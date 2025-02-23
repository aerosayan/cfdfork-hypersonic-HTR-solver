import "regent"
-------------------------------------------------------------------------------
-- IMPORTS
-------------------------------------------------------------------------------

local C = regentlib.c
local fabs = regentlib.fabs(double)
local sqrt = regentlib.sqrt(double)
local SCHEMA = terralib.includec("../../src/config_schema.h")
local REGISTRAR = terralib.includec("prometeo_metric.h")
local UTIL = require 'util-desugared'
local CONST = require "prometeo_const"

-- Reference solution
local r_e = terralib.newlist({2.727583789628854e+01, 2.589562063874777e+01, 2.222683878540408e+01, 1.888721148112942e+01, 1.647943543824111e+01, 1.469875285148004e+01, 1.345279880561839e+01, 1.266326779792019e+01, 1.228053238740288e+01, 1.228053238740287e+01, 1.266326779792020e+01, 1.345279880561836e+01, 1.469875285148006e+01, 1.647943543824112e+01, 1.888721148112938e+01, 2.222683878540410e+01, 2.589562063874781e+01, 2.727583789628854e+01})
local r_d = terralib.newlist({2.640364957342085e+01, 2.519516626875359e+01, 2.209511974977558e+01, 1.890177192361619e+01, 1.649926959969077e+01, 1.473669983655983e+01, 1.350335594761413e+01, 1.272177886064925e+01, 1.234288654510126e+01, 1.234288654510126e+01, 1.272177886064925e+01, 1.350335594761413e+01, 1.473669983655983e+01, 1.649926959969077e+01, 1.890177192361617e+01, 2.209511974977559e+01, 2.519516626875359e+01, 2.640364957342077e+01})
local r_s = terralib.newlist({5.280729914684170e+01, 2.409246486105948e+01, 2.040359422842343e+01, 1.760587770347194e+01, 1.552354538893888e+01, 1.402577225886651e+01, 1.301845891939099e+01, 1.243831970142641e+01, 1.224890666257680e+01, 1.243831970142641e+01, 1.301845891939099e+01, 1.402577225886651e+01, 1.552354538893888e+01, 1.760587770347192e+01, 2.040359422842341e+01, 2.409246486105955e+01, 5.280729914684154e+01, 1.000000000000000e+00})
local Ref_e = terralib.global(`arrayof(double, [r_e]))
local Ref_d = terralib.global(`arrayof(double, [r_d]))
local Ref_s = terralib.global(`arrayof(double, [r_s]))

-------------------------------------------------------------------------------
-- ACTIVATE ELECTRIC FIELD SOLVER
-------------------------------------------------------------------------------

local ELECTRIC_FIELD = false
if os.getenv("ELECTRIC_FIELD") == "1" then
   ELECTRIC_FIELD = true
   print("#############################################################################")
   print("WARNING: You are compiling with electric field solver.")
   print("#############################################################################")
end

local types_inc_flags = terralib.newlist({"-DEOS="..os.getenv("EOS")})
if ELECTRIC_FIELD then
   types_inc_flags:insert("-DELECTRIC_FIELD")
end
local TYPES = terralib.includec("prometeo_types.h", types_inc_flags)
local Fluid_columns = TYPES.Fluid_columns

--External modules
local MACRO = require "prometeo_macro"
local METRIC = (require 'prometeo_metric')(SCHEMA, TYPES, Fluid_columns)
local PART = (require 'prometeo_partitioner')(SCHEMA, METRIC, Fluid_columns)
local GRID = (require 'prometeo_grid')(SCHEMA, Fluid_columns, PART.zones_partitions)

-- Test parameters
local Npx = 16
local Npy = 16
local Npz = 16
local Nx = 2
local Ny = 2
local Nz = 2
local xO = 0.0
local yO = 0.0
local zO = 0.0
local xW = 1.0
local yW = 1.0
local zW = 1.0
local xGrid = SCHEMA.GridType_Tanh
local yGrid = SCHEMA.GridType_Tanh
local zGrid = SCHEMA.GridType_Tanh


__demand(__inline)
task InitializeCell(Fluid : region(ispace(int3d), Fluid_columns))
where
   writes(Fluid)
do
   fill(Fluid.centerCoordinates, array(0.0, 0.0, 0.0))
   fill(Fluid.cellWidth, array(0.0, 0.0, 0.0))
   fill(Fluid.nType_x, 0)
   fill(Fluid.nType_y, 0)
   fill(Fluid.nType_z, 0)
   fill(Fluid.dcsi_e, 0.0)
   fill(Fluid.deta_e, 0.0)
   fill(Fluid.dzet_e, 0.0)
   fill(Fluid.dcsi_d, 0.0)
   fill(Fluid.deta_d, 0.0)
   fill(Fluid.dzet_d, 0.0)
   fill(Fluid.dcsi_s, 0.0)
   fill(Fluid.deta_s, 0.0)
   fill(Fluid.dzet_s, 0.0)
end

__demand(__inline)
task checkMetric(Fluid : region(ispace(int3d), Fluid_columns))
where
   reads(Fluid.centerCoordinates),
   reads(Fluid.{dcsi_e, deta_e, dzet_e}),
   reads(Fluid.{dcsi_d, deta_d, dzet_d}),
   reads(Fluid.{dcsi_s, deta_s, dzet_s})
do
   for c in Fluid do
      -- Check x-direction
      regentlib.assert(fabs(Fluid[c].dcsi_e/Ref_e[c.x] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on dcsi_e")
      regentlib.assert(fabs(Fluid[c].dcsi_d/Ref_d[c.x] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on dcsi_d")
      regentlib.assert(fabs(Fluid[c].dcsi_s/Ref_s[c.x] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on dcsi_s")
      -- Check y-direction
      regentlib.assert(fabs(Fluid[c].deta_e/Ref_e[c.y] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on deta_e")
      regentlib.assert(fabs(Fluid[c].deta_d/Ref_d[c.y] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on deta_d")
      regentlib.assert(fabs(Fluid[c].deta_s/Ref_s[c.y] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on deta_s")
      -- Check z-direction
      regentlib.assert(fabs(Fluid[c].dzet_e/Ref_e[c.z] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on dzet_e")
      regentlib.assert(fabs(Fluid[c].dzet_d/Ref_d[c.z] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on dzet_d")
      regentlib.assert(fabs(Fluid[c].dzet_s/Ref_s[c.z] - 1.0) < 1e-12, "metricTest: error in Staggered Metric on dzet_s")
   end
end

task main()

   C.printf("metricTest_Staggered: run...\n")

   var config : SCHEMA.Config
   config.BC.xBCLeft.type  = SCHEMA.FlowBC_Dirichlet
   config.BC.xBCRight.type = SCHEMA.FlowBC_Dirichlet
   config.BC.yBCLeft.type  = SCHEMA.FlowBC_Dirichlet
   config.BC.yBCRight.type = SCHEMA.FlowBC_Dirichlet
   config.BC.zBCLeft.type  = SCHEMA.FlowBC_Dirichlet
   config.BC.zBCRight.type = SCHEMA.FlowBC_Dirichlet

   -- No ghost cells
   var xBnum = 1
   var yBnum = 1
   var zBnum = 1

   -- Define the domain
   var is_Fluid = ispace(int3d, {x = Npx + 2*xBnum,
                                 y = Npy + 2*yBnum,
                                 z = Npz + 2*zBnum})
   var Fluid = region(is_Fluid, Fluid_columns)
   var Fluid_bounds = Fluid.bounds

   -- Partitioning domain
   var tiles = ispace(int3d, {Nx, Ny, Nz})

   -- Fluid Partitioning
   var Fluid_Zones = PART.PartitionZones(Fluid, tiles, config, xBnum, yBnum, zBnum)
   var {p_All}= Fluid_Zones

   InitializeCell(Fluid)

   METRIC.InitializeOperators(Fluid, tiles, p_All)

   -- Enforce BCs on the operators
   __demand(__index_launch)
   for c in tiles do [METRIC.mkCorrectGhostOperators("x")](p_All[c], Fluid_bounds, config.BC.xBCLeft.type, config.BC.xBCRight.type, xBnum, Npx) end
   __demand(__index_launch)
   for c in tiles do [METRIC.mkCorrectGhostOperators("y")](p_All[c], Fluid_bounds, config.BC.yBCLeft.type, config.BC.yBCRight.type, yBnum, Npy) end
   __demand(__index_launch)
   for c in tiles do [METRIC.mkCorrectGhostOperators("z")](p_All[c], Fluid_bounds, config.BC.zBCLeft.type, config.BC.zBCRight.type, zBnum, Npz) end

   __demand(__index_launch)
   for c in tiles do
      GRID.InitializeGeometry(p_All[c],
                              xGrid, yGrid, zGrid,
                              1.0, 1.0, 1.0,
                              xBnum, Npx, xO, xW,
                              yBnum, Npy, yO, yW,
                              zBnum, Npz, zO, zW)
   end

   -- Create partitions to support stencils
   var Fluid_Ghosts = PART.PartitionGhost(Fluid, tiles, Fluid_Zones)
   var {p_MetricGhosts} = Fluid_Ghosts

   -- Enforce BCs
   GRID.InitializeGhostGeometry(Fluid, tiles, Fluid_Zones, config)

   __demand(__index_launch)
   for c in tiles do
      METRIC.InitializeMetric(p_MetricGhosts[c],
                              p_All[c],
                              Fluid_bounds,
                              xW, yW, zW);
   end

   -- Enforce BCs on the metric
   __demand(__index_launch)
   for c in tiles do [METRIC.mkCorrectGhostMetric("x")](p_All[c]) end
   __demand(__index_launch)
   for c in tiles do [METRIC.mkCorrectGhostMetric("y")](p_All[c]) end
   __demand(__index_launch)
   for c in tiles do [METRIC.mkCorrectGhostMetric("z")](p_All[c]) end

   checkMetric(Fluid)

   __fence(__execution, __block)

   C.printf("metricTest_Staggered: TEST OK!\n")
end

-------------------------------------------------------------------------------
-- COMPILATION CALL
-------------------------------------------------------------------------------

regentlib.saveobj(main, "metricTest_Staggered.o", "object", REGISTRAR.register_metric_tasks)
