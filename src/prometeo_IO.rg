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

return function(SCHEMA) local Exports = {}

-------------------------------------------------------------------------------
-- IMPORTS
-------------------------------------------------------------------------------
local C = regentlib.c
local MACRO = require 'prometeo_macro'
local UTIL = require 'util-desugared'

-------------------------------------------------------------------------------
-- I/O RUTINES
-------------------------------------------------------------------------------

-- regentlib.rexpr, regentlib.rexpr, regentlib.rexpr* -> regentlib.rquote
local function emitConsoleWrite(config_Mapping, format, ...)
   local args = terralib.newlist{...}
   return rquote
      var consoleFile = [&int8](C.malloc(256))
      C.snprintf(consoleFile, 256, '%s/console.txt', config_Mapping.outDir)
      var console = UTIL.openFile(consoleFile, 'a')
      C.free(consoleFile)
      C.fprintf(console, format, [args])
      C.fflush(console)
      C.fclose(console)
   end
end

-- MANUALLY PARALLELIZED, NO CUDA, NO OPENMP
task Exports.Console_WriteHeader(config_Mapping : SCHEMA.MappingStruct)
   [emitConsoleWrite(config_Mapping, '%10s'..
                                     '%15s'..
                                     '%13s'..
                                     '%15s'..
                                     '%15s'..
                                     '%15s'..
                                     '%15s\n',
                                     'Iter',
                                     'Sim Time',
                                     'Wall t',
                                     'Delta Time',
                                     'Avg Press',
                                     'Avg Temp',
                                     'Average KE')];
end

-- MANUALLY PARALLELIZED, NO CUDA, NO OPENMP
task Exports.Console_Write(config_Mapping : SCHEMA.MappingStruct,
                           Integrator_timeStep : int,
                           Integrator_simTime : double,
                           startTime : uint64,
                           Integrator_deltaTime : double,
                           Flow_averagePressure : double,
                           Flow_averageTemperature : double,
                           Flow_averageKineticEnergy : double)
   var currTime = C.legion_get_current_time_in_micros() / 1000;
   [emitConsoleWrite(config_Mapping, '%10d'..
                                     '%15.7e'..
                                     '%9llu.%03llu'..
                                     '%15.7e'..
                                     '%15.7e'..
                                     '%15.7e'..
                                     '%15.7e\n',
                     Integrator_timeStep,
                     Integrator_simTime,
                     rexpr (currTime - startTime) / 1000 end,
                     rexpr (currTime - startTime) % 1000 end,
                     Integrator_deltaTime,
                     Flow_averagePressure,
                     Flow_averageTemperature,
                     Flow_averageKineticEnergy)];
end

-- MANUALLY PARALLELIZED, NO CUDA, NO OPENMP
task Exports.Console_WriteFooter(config_Mapping : SCHEMA.MappingStruct,
                                 startTime : uint64)
   var endTime = C.legion_get_current_time_in_micros() / 1000;
   [emitConsoleWrite(config_Mapping,
                     'Total time: %llu.%03llu seconds\n',
                     rexpr (endTime - startTime) / 1000 end,
                     rexpr (endTime - startTime) % 1000 end)];
end

-- regentlib.rexpr, regentlib.rexpr, regentlib.rexpr, regentlib.rexpr*
--   -> regentlib.rquote
local function emitProbeWrite(config_Mapping, probeId, format, ...)
  local args = terralib.newlist{...}
  return rquote
    var filename = [&int8](C.malloc(256))
    C.snprintf(filename, 256, '%s/probe%d.csv', config_Mapping.outDir, probeId)
    var file = UTIL.openFile(filename, 'a')
    C.free(filename)
    C.fprintf(file, format, [args])
    C.fflush(file)
    C.fclose(file)
  end
end

-- MANUALLY PARALLELIZED, NO CUDA, NO OPENMP
task Exports.Probe_WriteHeader(config_Mapping : SCHEMA.MappingStruct,
                               probeId : int)
   [emitProbeWrite(config_Mapping, probeId, '%10s'..
                                            '%15s' ..
                                            '%15s' ..
                                            '%15s\n',
                                            'Iter',
                                            'Time',
                                            'Temperature',
                                            'Pressure')];
end

-- MANUALLY PARALLELIZED, NO CUDA, NO OPENMP
task Exports.Probe_Write(config_Mapping : SCHEMA.MappingStruct,
                         probeId : int,
                         Integrator_timeStep : int,
                         Integrator_simTime : double,
                         avgTemperature : double,
                         avgPressure : double)
   [emitProbeWrite(config_Mapping, probeId, '%10d'..
                                            '%15.7e' ..
                                            '%15.7e' ..
                                            '%15.7e\n',
                                            Integrator_timeStep,
                                            Integrator_simTime,
                                            avgTemperature,
                                            avgPressure)];
end

-- regentlib.rexpr, regentlib.rexpr, regentlib.rexpr* -> regentlib.rquote
local function emitTimingWrite(config_Mapping, format, ...)
   local args = terralib.newlist{...}
   return rquote
      var consoleFile = [&int8](C.malloc(256))
      C.snprintf(consoleFile, 256, '%s/timing.txt', config_Mapping.outDir)
      var console = UTIL.openFile(consoleFile, 'a')
      C.free(consoleFile)
      C.fprintf(console, format, [args])
      C.fflush(console)
      C.fclose(console)
   end
end

-- MANUALLY PARALLELIZED, NO CUDA, NO OPENMP
task Exports.Console_WriteTiming( _ : int,
                                  config_Mapping : SCHEMA.MappingStruct,
                                  taskname : regentlib.string,
                                  line : int,
                                  currTime : uint64)
   [emitTimingWrite(config_Mapping,
                    "TIMING: %s task is on line %d at time %llu.%06llu\n",
                    taskname,
                    line,
                    rexpr currTime / 1000000 end,
                    rexpr currTime % 1000000 end)];
   return _
end

-- MANUALLY PARALLELIZED, NO CUDA, NO OPENMP
task Exports.createDir(_ : int, dirname : regentlib.string)
   UTIL.createDir(dirname)
   return _
end

return Exports end

