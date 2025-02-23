// Copyright (c) "2019, by Stanford University
//               Developer: Mario Di Renzo
//               Affiliation: Center for Turbulence Research, Stanford University
//               URL: https://ctr.stanford.edu
//               Citation: Di Renzo, M., Lin, F., and Urzay, J. (2020).
//                         HTR solver: An open-source exascale-oriented task-based
//                         multi-GPU high-order code for hypersonic aerothermodynamics.
//                         Computer Physics Communications 255, 107262"
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef __PROMETEO_CFL_HPP__
#define __PROMETEO_CFL_HPP__

#include "legion.h"

using namespace Legion;

//-----------------------------------------------------------------------------
// LOAD PROMETEO UTILITIES AND MODULES
//-----------------------------------------------------------------------------

#include "task_helper.hpp"
#include "PointDomain_helper.hpp"
#include "prometeo_types.h"
#include "prometeo_cfl.h"

//-----------------------------------------------------------------------------
// TASK THAT COMPUTES THE CFL NUMBER
//-----------------------------------------------------------------------------

#ifndef __CUDACC__
using std::max;
using std::min;
#endif

class CalculateMaxSpectralRadiusTask {
public:
   struct Args {
      uint64_t arg_mask[1];
      LogicalRegion Fluid;
      LogicalRegion ModCells;
      Mix mix;
      FieldID Fluid_fields      [FID_last - 101];
      FieldID ModCells_fields   [FID_last - 101];
   };
public:
   static const char * const TASK_NAME;
   static const int TASK_ID;
   static const bool CPU_BASE_LEAF = true;
   static const bool GPU_BASE_LEAF = true;
   static const int MAPPER_ID = 0;
private:
   __CUDA_H__
   static inline double CalculateConvectiveSpectralRadius(const   Vec3 &cellWidth,
                                                          const   Vec3 &velocity,
                                                          const double SoS) {
      double r = 0.0; // Spectral radius cannot be lower than 0
      __UNROLL__
      for (int i = 0; i < 3; i++)
         r = max(r, (fabs(velocity[i]) + SoS)/cellWidth[i]);
      return r;
   };

   __CUDA_H__
   static inline double CalculateViscousSpectralRadius(const   Vec3 &cellWidth,
                                                       const double rho,
                                                       const double mu) {
      const double nu = mu/rho;
      double r = 0.0; // Spectral radius cannot be lower than 0
      __UNROLL__
      for (int i = 0; i < 3; i++)
         r = max(r, nu/(cellWidth[i]*cellWidth[i]));
      r *= 4;
      return r;
   };

   __CUDA_H__
   static inline double CalculateHeatConductionSpectralRadius(const   Vec3 &cellWidth,
                                                              const double temperature,
                                                              const VecNSp &MassFracs,
                                                              const double rho,
                                                              const double lam,
                                                              const    Mix &mix) {
      const double cp = mix.GetHeatCapacity(temperature, MassFracs);
      const double DifT = lam/(cp*rho);
      double r = 0.0; // Spectral radius cannot be lower than 0
      __UNROLL__
      for (int i = 0; i < 3; i++)
         r = max(r, DifT/(cellWidth[i]*cellWidth[i]));
      r *= 4;
      return r;
   };

   __CUDA_H__
   static inline double CalculateSpeciesDiffusionSpectralRadius(const   Vec3 &cellWidth,
                                                                const VecNSp &Di) {
      double r = 0.0; // Spectral radius cannot be lower than 0
      for (int s = 0; s < nSpec; s++)
         __UNROLL__
         for (int i = 0; i < 3; i++)
            r = max(r, Di[s]/(cellWidth[i]*cellWidth[i]));
      r *= 4;
      return r;
   };

#if (defined(ELECTRIC_FIELD) && (nIons > 0))
   __CUDA_H__
   static inline double CalculateSpeciesDriftSpectralRadius(const   Vec3 &eField,
                                                            const   Vec3 &cellWidth,
                                                            const VecNIo &Ki) {
      double r = 0.0; // Spectral radius cannot be lower than 0
      __UNROLL__
      for (int i = 0; i < 3; i++)
         r = max(r, fabs(eField[i])/cellWidth[i]);
      // Compute the maximum electric mobility
      double Kimax = 0.0;
      __UNROLL__
      for (int i = 0; i < nIons; i++)
         Kimax = max(Kimax, Ki[i]);
      r *= Kimax;
      return r;
   };
#endif

public:
   __CUDA_H__
   static inline double CalculateMaxSpectralRadius(const AccessorRO<  Vec3, 3> &cellWidth,
                                                   const AccessorRO<double, 3> &temperature,
                                                   const AccessorRO<VecNSp, 3> &MassFracs,
                                                   const AccessorRO<  Vec3, 3> &velocity,
                                                   const AccessorRO<double, 3> &rho,
                                                   const AccessorRO<double, 3> &mu,
                                                   const AccessorRO<double, 3> &lam,
                                                   const AccessorRO<VecNSp, 3> &Di,
                                                   const AccessorRO<double, 3> &SoS,
#if (defined(ELECTRIC_FIELD) && (nIons > 0))
                                                   const AccessorRO<VecNIo, 3> &Ki,
                                                   const AccessorRO<  Vec3, 3> &eField,
#endif
                                                   const Point<3> &p,
                                                   const      Mix &mix) {
      double r = 0.0; // Spectral radius cannot be lower than 0
      r = max(r, CalculateConvectiveSpectralRadius(cellWidth[p], velocity[p], SoS[p]));
      r = max(r, CalculateViscousSpectralRadius(cellWidth[p], rho[p], mu[p]));
      r = max(r, CalculateHeatConductionSpectralRadius(cellWidth[p],
                                                       temperature[p], MassFracs[p],
                                                       rho[p], lam[p], mix));
      r = max(r, CalculateSpeciesDiffusionSpectralRadius(cellWidth[p], Di[p]));
#if (defined(ELECTRIC_FIELD) && (nIons > 0))
      r = max(r, CalculateSpeciesDriftSpectralRadius(eField[p], cellWidth[p], Ki[p]));
#endif
      return r;
   }
public:
   static double cpu_base_impl(const Args &args,
                             const std::vector<PhysicalRegion> &regions,
                             const std::vector<Future>         &futures,
                             Context ctx, Runtime *runtime);
#ifdef LEGION_USE_CUDA
   static DeferredValue<double> gpu_base_impl(const Args &args,
                             const std::vector<PhysicalRegion> &regions,
                             const std::vector<Future>         &futures,
                             Context ctx, Runtime *runtime);
#endif
};

#endif // __PROMETEO_CFL_HPP__
