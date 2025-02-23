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

#ifndef MultiComponent_HPP
#define MultiComponent_HPP

#ifndef nSpec
   #error "nSpec is undefined"
#endif

//#ifndef nReac
//   #error "nReac is undefined"
//#endif

//#ifndef nTBReac
//   #error "nTBReac is undefined"
//#endif

//#ifndef nFOReac
//   #error "nFOReac is undefined"
//#endif

#ifndef MAX_NUM_REACTANTS
   #error "MAX_NUM_REACTANTS is undefined"
#endif

#ifndef MAX_NUM_TB
   #error "MAX_NUM_TB is undefined"
#endif

#ifndef __CUDA_HD__
#ifdef __CUDACC__
#define __CUDA_HD__ __host__ __device__
#else
#define __CUDA_HD__
#endif
#endif

#ifndef __UNROLL__
#ifdef __CUDACC__
#define __UNROLL__ #pragma unroll
#else
#define __UNROLL__
#endif
#endif

#ifndef __CONST__
#ifdef __CUDACC__
#define __CONST__
#else
#define __CONST__ const
#endif
#endif

#undef CHECK_MIX

#include <string.h>
#include "config_schema.h"
#include "constants.h"
#include "Species.hpp"
#include "Reaction.hpp"

#ifdef __cplusplus
   // We cannot expose these structs to Regent
   #include "my_array.hpp"

   #ifndef __CUDACC__
   using std::max;
   using std::min;
   #endif

   // Define type for the array that will contain the species
   typedef MyArray<double, nSpec> VecNSp;
#if (nIons > 0)
   typedef MyArray<double, nIons> VecNIo;
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct Mix {
   __CONST__ struct Spec species[nSpec];
#if (nIons > 0)
   __CONST__ uint8_t ions[nIons]; // Stores a list of the indices of the ions
#endif
#if (nReac > 0)
   __CONST__ struct Reaction reactions[nReac];
#endif
#if (nTBReac > 0)
   __CONST__ struct ThirdbodyReaction ThirdbodyReactions[nTBReac];
#endif
#if (nFOReac > 0)
   __CONST__ struct FalloffReaction FalloffReactions[nFOReac];
#endif
   // Normalization quantities
   double PRef;                   // Reference pressure
   double TRef;                   // Reference temperature
   double XiRef[nSpec];           // Reference molar fractions
   double MixWRef;                // Reference mean molecular weight
   double iMixWRef;               // Inverse of the reference mean molecular weight
   double rhoRef;                 // Reference density
   double ieRef;                  // Inverse of the reference energy scale
   double iuRef;                  // Inverse of the reference velocity scale
   double iCpRef;                 // Inverse of the reference heat capacity scale
   double imuRef;                 // Inverse of the reference viscosity scale
   double ilamRef;                // Inverse of the reference heat conductivity scale
   double iDiRef;                 // Inverse of the reference species diffusivity scale
   double iwiRef;                 // Inverse of the reference chemical production rate scale
   double iKiRef;                 // Inverse of the reference species electric mobility scale
   double Eps0;                   // Normalized dielectric permittivity of the vacuum
   // Max an min acceptable temperatures
   double TMax;
   double TMin;

#ifdef __cplusplus
   // We cannot expose these methods to Regent

#ifndef __CUDACC__
   inline Mix(const Config &config);
#endif

   inline char* GetSpeciesName(const int i) const;

   inline int FindSpecies(const char *Name) const;

   __CUDA_HD__
   inline bool CheckMixture(const VecNSp &Yi) const;

   __CUDA_HD__
   inline void ClipYi(VecNSp &Yi) const;

   __CUDA_HD__
   inline double GetMolarWeightFromYi(const VecNSp &Yi) const;

   __CUDA_HD__
   inline double GetMolarWeightFromXi(const VecNSp &Xi) const;

   __CUDA_HD__
   inline void GetMolarFractions(VecNSp &Xi, const double MixW, const VecNSp &Yi) const;

   __CUDA_HD__
   inline void GetMassFractions(VecNSp &Yi, const double MixW, const VecNSp &Xi) const;

   __CUDA_HD__
   inline void GetYi(VecNSp &Yi, const double rho, const VecNSp &rhoYi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetRhoFromRhoYi(const VecNSp &rhoYi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline void GetRhoYiFromYi(VecNSp &rhoYi, const double rho, const VecNSp &Yi) const;

   // Returns rho in physical units
   __CUDA_HD__
   inline double GetRhoRef(const double P, const double T, const double MixW) const;

   // Returns rho in computational units
   __CUDA_HD__
   inline double GetRho(const double P, const double T, const double MixW) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetHeatCapacity(const double T, const VecNSp &Yi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetEnthalpy(const double T, const VecNSp &Yi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetSpeciesEnthalpy(const int i, const double T) const;

   __CUDA_HD__
   inline double GetSpeciesMolarWeight(const int i) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetInternalEnergy(const double T, const VecNSp &Yi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetSpecificInternalEnergy(const int i, const double T) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetTFromInternalEnergy(const double e0, double T, const VecNSp &Yi) const;

   // The input are in computational units
   __CUDA_HD__
   inline double isValidInternalEnergy(const double e, const VecNSp &Yi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetTFromRhoAndP(const double rho, const double MixW, const double P) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetPFromRhoAndT(const double rho, const double MixW, const double T) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetViscosity(const double T, const VecNSp &Xi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetHeatConductivity(const double T, const VecNSp &Xi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetGamma(const double T, const double MixW, const VecNSp &Yi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetSpeedOfSound(const double T, const double gamma, const double MixW) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline void GetDiffusivity(VecNSp &Di, const double P, const double T, const double MixW, const VecNSp &Xi) const;

#if (nIons > 0)
   // The input and the outputs are in computational units
   __CUDA_HD__
   inline void GetElectricMobility(VecNIo &Ki, const double Pn, const double Tn, const VecNSp &Xi) const;
#endif

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetPartialElectricChargeDensity(const uint8_t i, const double rhon, const double MixW, const VecNSp &Xi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double GetElectricChargeDensity(const double rhon, const double MixW, const VecNSp &Xi) const;

   __CUDA_HD__
   inline int8_t GetSpeciesChargeNumber(const int i) const;

   // The output is in computational units
   __CUDA_HD__
   inline double GetDielectricPermittivity() const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline void GetProductionRates(VecNSp &w, const double rhon, const double Pn, const double Tn, const VecNSp &Yi) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline double Getdpde(const double rho, const double gamma) const;

   // The input and the outputs are in computational units
   __CUDA_HD__
   inline void Getdpdrhoi(VecNSp &dpdrhoi, const double gamma, const double T, const VecNSp &Yi) const;

private:

   inline void StoreReferenceQuantities(const double PRef, const double TRef, const double LRef, const Mixture &XiRef);

#endif // __cplusplus
};

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// We cannot expose these methods to Regent
#include "MultiComponent.inl"
#endif

#endif // MultiComponent_HPP
