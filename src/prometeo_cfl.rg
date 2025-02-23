-- Copyright (c) "2019, by Stanford University
--               Developer: Mario Di Renzo
--               Affiliation: Center for Turbulence Research, Stanford University
--               URL: https://ctr.stanford.edu
--               Citation: Di Renzo, M., Lin, F., and Urzay, J. (2020).
--                         HTR solver: An open-source exascale-oriented task-based
--                         multi-GPU high-order code for hypersonic aerothermodynamics.
--                         Computer Physics Communications 255, 107262"
-- All rights reserved.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions are met:
--    * Redistributions of source code must retain the above copyright
--      notice, this list of conditions and the following disclaimer.
--    * Redistributions in binary form must reproduce the above copyright
--      notice, this list of conditions and the following disclaimer in the
--      documentation and/or other materials provided with the distribution.
--
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
-- ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
-- WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
-- DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
-- DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
-- (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
-- LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
-- ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
-- (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
-- SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import "regent"

return function(MIX, TYPES, ELECTRIC_FIELD) local Exports = {}

-------------------------------------------------------------------------------
-- IMPORTS
-------------------------------------------------------------------------------
local C = regentlib.c

local Fluid_columns = TYPES.Fluid_columns

-------------------------------------------------------------------------------
-- STABILITY CONDITIONS ROUTINES
-------------------------------------------------------------------------------

local Prop = terralib.newlist({"rho", "mu", "lam", "Di", "SoS"})
local Vars = terralib.newlist({"velocity", "MassFracs", "temperature"})
if (ELECTRIC_FIELD and (MIX.nIons > 0)) then
   Prop:insert("Ki")
   Vars:insert("electricField")
end
extern task Exports.CalculateMaxSpectralRadius(Fluid : region(ispace(int3d), Fluid_columns),
                                               ModCells : region(ispace(int3d), Fluid_columns),
                                               mix : MIX.Mixture) : double
where
   reads(Fluid.cellWidth),
   reads(Fluid.[Prop]),
   reads(Fluid.[Vars])
end
Exports.CalculateMaxSpectralRadius:set_task_id(TYPES.TID_CalculateMaxSpectralRadius)

return Exports end

