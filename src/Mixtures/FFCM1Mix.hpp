// Copyright (c) "2020, by Centre Européen de Recherche et de Formation Avancée en Calcul Scientifiq
//               Developer: Mario Di Renzo
//               Affiliation: Centre Européen de Recherche et de Formation Avancée en Calcul Scientifique
//               URL: https://cerfacs.fr
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


#ifndef __FFCM1MIX_HPP__
#define __FFCM1MIX_HPP__

// Number of species
#define nSpec 33
// Number of charged species
#define nIons 0
// Number of standard reactions
#define nReac 224
// Number of thirdbody reactions
#define nTBReac 5
// Number of falloff reactions
#define nFOReac 30
// Maximum number of reactants in a reaction
#define MAX_NUM_REACTANTS 2
// Maximum number of products in a reaction
#define MAX_NUM_PRODUCTS 3
// Maximum number of colliders in a reaction
#define MAX_NUM_TB 10
// Number of Nasa polynomials
#define N_NASA_POLY 2
// Switch to mass action kinetics
#undef FWD_ORDERS

#include "MultiComponent.hpp"

#ifdef __cplusplus
// We cannot expose these methods to Regent

//---------------------------------
// Define Species
//---------------------------------

// H2
#define iH2 0
#define     H2 { \
   /*      Name = */       (char*)("H2"), \
   /*         W = */       0.00100784*2, \
   /*       inx = */       iH2, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  2.932865750E+00,  8.266080260E-04, -1.464023640E-07,  1.541004140E-11, -6.888048000E-16, -8.130655810E+02, -1.024328650E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  2.344331120E+00,  7.980520750E-03, -1.947815100E-05,  2.015720940E-08, -7.376117610E-12, -9.179351730E+02,  6.830102380E-01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 2.92*ATom, \
         /*   kbOveps = */ 1.0/38.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.79*ATom*ATom*ATom, \
         /*      Z298 = */ 280.0 \
                              } \
               }

// H
#define iH 1
#define      H { \
   /*      Name = */       (char*)("H"), \
   /*         W = */       0.00100784*1, \
   /*       inx = */       iH, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  2.500000000E+00,  0.000000000E+00,  0.000000000E+00,  0.000000000E+00,  0.000000000E+00,  2.547366000E+04, -4.466828500E-01 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  2.500000000E+00,  0.000000000E+00,  0.000000000E+00,  0.000000000E+00,  0.000000000E+00,  2.547366000E+04, -4.466828500E-01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Atom, \
         /*     sigma = */ 2.05*ATom, \
         /*   kbOveps = */ 1.0/145.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// O
#define iO 2
#define      O { \
   /*      Name = */       (char*)("O"), \
   /*         W = */       0.0159994*1, \
   /*       inx = */       iO, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  2.543636970E+00, -2.731624860E-05, -4.190295200E-09,  4.954818450E-12, -4.795536940E-16,  2.922601200E+04,  4.922294570E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.168267100E+00, -3.279318840E-03,  6.643063960E-06, -6.128066240E-09,  2.112659710E-12,  2.912225920E+04,  2.051933460E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Atom, \
         /*     sigma = */ 2.75*ATom, \
         /*   kbOveps = */ 1.0/80.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// O2
#define iO2 3
#define     O2 { \
   /*      Name = */       (char*)("O2"), \
   /*         W = */       0.0159994*2, \
   /*       inx = */       iO2, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.660960650E+00,  6.563658110E-04, -1.411496270E-07,  2.057979350E-11, -1.299134360E-15, -1.215977180E+03,  3.415362790E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.782456360E+00, -2.996734160E-03,  9.847302010E-06, -9.681295090E-09,  3.243728370E-12, -1.063943560E+03,  3.657675730E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 3.458*ATom, \
         /*   kbOveps = */ 1.0/107.4, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 1.6*ATom*ATom*ATom, \
         /*      Z298 = */ 3.8 \
                              } \
               }

// OH
#define iOH 4
#define     OH { \
   /*      Name = */       (char*)("OH"), \
   /*         W = */       0.00100784*1+0.0159994*1, \
   /*       inx = */       iOH, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  2.838530330E+00,  1.107412890E-03, -2.940002090E-07,  4.206987290E-11, -2.422898900E-15,  3.697808080E+03,  5.844946520E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.991984240E+00, -2.401066550E-03,  4.616640330E-06, -3.879163060E-09,  1.363195020E-12,  3.368898360E+03, -1.039984770E-01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 2.75*ATom, \
         /*   kbOveps = */ 1.0/80.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// H2O
#define iH2O 5
#define    H2O { \
   /*      Name = */       (char*)("H2O"), \
   /*         W = */       0.00100784*2+0.0159994*1, \
   /*       inx = */       iH2O, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  2.677038900E+00,  2.973181600E-03, -7.737688900E-07,  9.443351400E-11, -4.268999100E-15, -2.988589400E+04,  6.882550000E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.198635200E+00, -2.036401700E-03,  6.520341600E-06, -5.487926900E-09,  1.771968000E-12, -3.029372600E+04, -8.490090100E-01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 2.605*ATom, \
         /*   kbOveps = */ 1.0/572.4, \
         /*        mu = */ 1.844*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 4.0 \
                              } \
               }

// HO2
#define iHO2 6
#define    HO2 { \
   /*      Name = */       (char*)("HO2"), \
   /*         W = */       0.00100784*1+0.0159994*2, \
   /*       inx = */       iHO2, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          5000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          5000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.172287410E+00,  1.881176270E-03, -3.462772860E-07,  1.946575490E-11,  1.762569050E-16,  3.102068390E+01,  2.957676720E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.301798070E+00, -4.749120970E-03,  2.115829050E-05, -2.427639140E-08,  9.292252250E-12,  2.640184850E+02,  3.716662200E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.458*ATom, \
         /*   kbOveps = */ 1.0/107.4, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 1.0 \
                              } \
               }

// H2O2
#define iH2O2 7
#define   H2O2 { \
   /*      Name = */       (char*)("H2O2"), \
   /*         W = */       0.00100784*2+0.0159994*2, \
   /*       inx = */       iH2O2, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.579773050E+00,  4.053260030E-03, -1.298447300E-06,  1.982114000E-10, -1.139687920E-14, -1.800717750E+04,  6.649706940E-01 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.315151490E+00, -8.473906220E-04,  1.764043230E-05, -2.267629440E-08,  9.089501580E-12, -1.770674370E+04,  3.273733190E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.458*ATom, \
         /*   kbOveps = */ 1.0/107.4, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 3.8 \
                              } \
               }

// CO
#define iCO 8
#define     CO { \
   /*      Name = */       (char*)("CO"), \
   /*         W = */       0.0120107*1+0.0159994*1, \
   /*       inx = */       iCO, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.048485900E+00,  1.351728100E-03, -4.857940500E-07,  7.885364400E-11, -4.698074600E-15, -1.426611700E+04,  6.017097700E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.579533500E+00, -6.103536900E-04,  1.016814300E-06,  9.070058600E-10, -9.044244900E-13, -1.434408600E+04,  3.508409300E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 3.65*ATom, \
         /*   kbOveps = */ 1.0/98.1, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 1.95*ATom*ATom*ATom, \
         /*      Z298 = */ 1.8 \
                              } \
               }

// CO2
#define iCO2 9
#define    CO2 { \
   /*      Name = */       (char*)("CO2"), \
   /*         W = */       0.0120107*1+0.0159994*2, \
   /*       inx = */       iCO2, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.636511100E+00,  2.741456900E-03, -9.958975900E-07,  1.603866600E-10, -9.161985700E-15, -4.902490400E+04, -1.934895500E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  2.356813000E+00,  8.984129900E-03, -7.122063200E-06,  2.457300800E-09, -1.428854800E-13, -4.837197100E+04,  9.900903500E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 3.763*ATom, \
         /*   kbOveps = */ 1.0/244.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 2.65*ATom*ATom*ATom, \
         /*      Z298 = */ 2.1 \
                              } \
               }

// C
#define iC 10
#define      C { \
   /*      Name = */       (char*)("C"), \
   /*         W = */       0.0120107*1, \
   /*       inx = */       iC, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  2.605583000E+00, -1.959343400E-04,  1.067372200E-07, -1.642394000E-11,  8.187058000E-16,  8.541174200E+04,  4.192386800E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  2.554239500E+00, -3.215377200E-04,  7.337922300E-07, -7.322348700E-10,  2.665214400E-13,  8.544268100E+04,  4.531308500E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Atom, \
         /*     sigma = */ 3.298*ATom, \
         /*   kbOveps = */ 1.0/71.4, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// CH
#define iCH 11
#define     CH { \
   /*      Name = */       (char*)("CH"), \
   /*         W = */       0.0120107*1+0.00100784*1, \
   /*       inx = */       iCH, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  2.520936900E+00,  1.765363900E-03, -4.614766000E-07,  5.928967500E-11, -3.347450100E-15,  7.094676900E+04,  7.405182900E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.489758300E+00,  3.243216000E-04, -1.689975100E-06,  3.162842000E-09, -1.406180300E-12,  7.061264600E+04,  2.084284100E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 2.75*ATom, \
         /*   kbOveps = */ 1.0/80.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// CH2
#define iCH2 12
#define    CH2 { \
   /*      Name = */       (char*)("CH2"), \
   /*         W = */       0.0120107*1+0.00100784*2, \
   /*       inx = */       iCH2, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.146318860E+00,  3.036712590E-03, -9.964744390E-07,  1.504835800E-10, -8.573355150E-15,  4.604126050E+04,  4.723417110E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.717578460E+00,  1.273912600E-03,  2.173472510E-06, -3.488585000E-09,  1.652088660E-12,  4.587238660E+04,  1.752979450E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 3.8*ATom, \
         /*   kbOveps = */ 1.0/144.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// CH2(S)
#define iCH2_S 13
#define  CH2_S { \
   /*      Name = */       (char*)("CH2(S)"), \
   /*         W = */       0.0120107*1+0.00100784*2, \
   /*       inx = */       iCH2_S, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.135016860E+00,  2.895939260E-03, -8.166680900E-07,  1.135726970E-10, -6.362628350E-15,  5.050405040E+04,  4.060306210E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.193313250E+00, -2.331051840E-03,  8.156764510E-06, -6.629859810E-09,  1.932331990E-12,  5.036622460E+04, -7.467343100E-01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 3.8*ATom, \
         /*   kbOveps = */ 1.0/144.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// CH3
#define iCH3 14
#define    CH3 { \
   /*      Name = */       (char*)("CH3"), \
   /*         W = */       0.0120107*1+0.00100784*3, \
   /*       inx = */       iCH3, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  2.978120600E+00,  5.797852000E-03, -1.975580000E-06,  3.072979000E-10, -1.791741600E-14,  1.650951300E+04,  4.722479900E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.657179700E+00,  2.126597900E-03,  5.458388300E-06, -6.618100300E-09,  2.465707400E-12,  1.642271600E+04,  1.673535400E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 3.8*ATom, \
         /*   kbOveps = */ 1.0/144.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// CH4
#define iCH4 15
#define    CH4 { \
   /*      Name = */       (char*)("CH4"), \
   /*         W = */       0.0120107*1+0.00100784*4, \
   /*       inx = */       iCH4, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  1.653262260E+00,  1.002630990E-02, -3.316612380E-06,  5.364831380E-10, -3.146967580E-14, -1.000959360E+04,  9.905062830E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  5.149114680E+00, -1.366220090E-02,  4.914539210E-05, -4.842467670E-08,  1.666034410E-11, -1.024659830E+04, -4.638488420E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.746*ATom, \
         /*   kbOveps = */ 1.0/141.4, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 2.6*ATom*ATom*ATom, \
         /*      Z298 = */ 13.0 \
                              } \
               }

// HCO
#define iHCO 16
#define    HCO { \
   /*      Name = */       (char*)("HCO"), \
   /*         W = */       0.0120107*1+0.00100784*1+0.0159994*1, \
   /*       inx = */       iHCO, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.920015420E+00,  2.522793240E-03, -6.710041640E-07,  1.056159480E-10, -7.437982610E-15,  3.653429280E+03,  3.580770560E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.237546100E+00, -3.320752570E-03,  1.400302640E-05, -1.342399950E-08,  4.374162080E-12,  3.872411850E+03,  3.308348690E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.59*ATom, \
         /*   kbOveps = */ 1.0/498.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 0.0 \
                              } \
               }

// CH2O
#define iCH2O 17
#define   CH2O { \
   /*      Name = */       (char*)("CH2O"), \
   /*         W = */       0.0120107*1+0.00100784*2+0.0159994*1, \
   /*       inx = */       iCH2O, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.169526650E+00,  6.193205600E-03, -2.250563660E-06,  3.659756600E-10, -2.201494580E-14, -1.454868310E+04,  6.042078980E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.793723120E+00, -9.908333220E-03,  3.732199900E-05, -3.792852370E-08,  1.317726410E-11, -1.437919530E+04,  6.027980580E-01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.59*ATom, \
         /*   kbOveps = */ 1.0/498.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.0 \
                              } \
               }

// CH2OH
#define iCH2OH 18
#define  CH2OH { \
   /*      Name = */       (char*)("CH2OH"), \
   /*         W = */       0.0120107*1+0.00100784*3+0.0159994*1, \
   /*       inx = */       iCH2OH, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  5.093143700E+00,  5.947612600E-03, -2.064974600E-06,  3.230081730E-10, -1.881259020E-14, -4.034096400E+03, -1.846914930E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.478343670E+00, -1.350703100E-03,  2.784849800E-05, -3.648690600E-08,  1.479074500E-11, -3.500728900E+03,  3.309135000E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.69*ATom, \
         /*   kbOveps = */ 1.0/417.0, \
         /*        mu = */ 1.7*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.0 \
                              } \
               }

// CH3O
#define iCH3O 19
#define   CH3O { \
   /*      Name = */       (char*)("CH3O"), \
   /*         W = */       0.0120107*1+0.00100784*3+0.0159994*1, \
   /*       inx = */       iCH3O, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.757792380E+00,  7.441424740E-03, -2.697051760E-06,  4.380905040E-10, -2.635370980E-14,  3.781119400E+02, -1.966800280E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.711805020E+00, -2.804633060E-03,  3.765509710E-05, -4.730720890E-08,  1.865884200E-11,  1.295697600E+03,  6.572408640E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.69*ATom, \
         /*   kbOveps = */ 1.0/417.0, \
         /*        mu = */ 1.7*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.0 \
                              } \
               }

// CH3OH
#define iCH3OH 20
#define  CH3OH { \
   /*      Name = */       (char*)("CH3OH"), \
   /*         W = */       0.0120107*1+0.00100784*4+0.0159994*1, \
   /*       inx = */       iCH3OH, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.527267950E+00,  1.031787830E-02, -3.628929440E-06,  5.774480160E-10, -3.421826320E-14, -2.600288340E+04,  5.167586930E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  5.658510510E+00, -1.629834190E-02,  6.919381560E-05, -7.583729260E-08,  2.804275500E-11, -2.561197360E+04, -8.973305080E-01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.626*ATom, \
         /*   kbOveps = */ 1.0/481.8, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 1.0 \
                              } \
               }

// C2H
#define iC2H 21
#define    C2H { \
   /*      Name = */       (char*)("C2H"), \
   /*         W = */       0.0120107*2+0.00100784*1, \
   /*       inx = */       iC2H, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.662702480E+00,  3.824922520E-03, -1.366325000E-06,  2.134550400E-10, -1.232168480E-14,  6.716837900E+04,  3.922057920E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  2.898676760E+00,  1.329884890E-02, -2.807333270E-05,  2.894847550E-08, -1.075023510E-11,  6.706160500E+04,  6.185476320E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 4.1*ATom, \
         /*   kbOveps = */ 1.0/209.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.5 \
                              } \
               }

// C2H2
#define iC2H2 22
#define   C2H2 { \
   /*      Name = */       (char*)("C2H2"), \
   /*         W = */       0.0120107*2+0.00100784*2, \
   /*       inx = */       iC2H2, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.658784890E+00,  4.883966670E-03, -1.608288880E-06,  2.469745440E-10, -1.386059590E-14,  2.575940420E+04, -3.998381940E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  8.086796820E-01,  2.336157620E-02, -3.551722340E-05,  2.801529580E-08, -8.500751650E-12,  2.642898080E+04,  1.393967610E+01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_Linear, \
         /*     sigma = */ 4.1*ATom, \
         /*   kbOveps = */ 1.0/209.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.5 \
                              } \
               }

// C2H3
#define iC2H3 23
#define   C2H3 { \
   /*      Name = */       (char*)("C2H3"), \
   /*         W = */       0.0120107*2+0.00100784*3, \
   /*       inx = */       iC2H3, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.150267630E+00,  7.540213410E-03, -2.629978470E-06,  4.159740480E-10, -2.454075090E-14,  3.385663800E+04,  1.728122350E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.363776420E+00,  2.657657220E-04,  2.796207040E-05, -3.729869420E-08,  1.515901760E-11,  3.447495890E+04,  7.915100920E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 4.1*ATom, \
         /*   kbOveps = */ 1.0/209.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 1.0 \
                              } \
               }

// C2H4
#define iC2H4 24
#define   C2H4 { \
   /*      Name = */       (char*)("C2H4"), \
   /*         W = */       0.0120107*2+0.00100784*4, \
   /*       inx = */       iC2H4, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  3.991827240E+00,  1.048339080E-02, -3.717213420E-06,  5.946283660E-10, -3.536303860E-14,  4.268658510E+03, -2.690817620E-01 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.959200630E+00, -7.570513730E-03,  5.709899930E-05, -6.915883520E-08,  2.698841900E-11,  5.089775980E+03,  4.097302130E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.971*ATom, \
         /*   kbOveps = */ 1.0/280.8, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 1.5 \
                              } \
               }

// C2H5
#define iC2H5 25
#define   C2H5 { \
   /*      Name = */       (char*)("C2H5"), \
   /*         W = */       0.0120107*2+0.00100784*5, \
   /*       inx = */       iC2H5, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.321956330E+00,  1.239305420E-02, -4.396809600E-06,  7.035199170E-10, -4.184352390E-14,  1.217594750E+04,  1.711038090E-01 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.241859050E+00, -3.569052350E-03,  4.826672020E-05, -5.854010090E-08,  2.258045140E-11,  1.296903440E+04,  4.447037820E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 4.302*ATom, \
         /*   kbOveps = */ 1.0/252.3, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 1.5 \
                              } \
               }

// C2H6
#define iC2H6 26
#define   C2H6 { \
   /*      Name = */       (char*)("C2H6"), \
   /*         W = */       0.0120107*2+0.00100784*6, \
   /*       inx = */       iC2H6, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.046664110E+00,  1.535388020E-02, -5.470394850E-06,  8.778265440E-10, -5.231675310E-14, -1.244734990E+04, -9.686983130E-01 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.291425720E+00, -5.501549010E-03,  5.994384580E-05, -7.084664690E-08,  2.686858360E-11, -1.152220560E+04,  2.666789940E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 4.302*ATom, \
         /*   kbOveps = */ 1.0/252.3, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 1.5 \
                              } \
               }

// HCCO
#define iHCCO 27
#define   HCCO { \
   /*      Name = */       (char*)("HCCO"), \
   /*         W = */       0.0120107*2+0.00100784*1+0.0159994*1, \
   /*       inx = */       iHCCO, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  5.914793330E+00,  3.714087300E-03, -1.301370100E-06,  2.064733450E-10, -1.214767590E-14,  1.935963010E+04, -5.505672690E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  1.876079690E+00,  2.212054180E-02, -3.588693250E-05,  3.054025410E-08, -1.012810690E-11,  2.016338400E+04,  1.369682900E+01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 2.5*ATom, \
         /*   kbOveps = */ 1.0/150.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 1.0 \
                              } \
               }

// CH2CO
#define iCH2CO 28
#define  CH2CO { \
   /*      Name = */       (char*)("CH2CO"), \
   /*         W = */       0.0120107*2+0.00100784*2+0.0159994*1, \
   /*       inx = */       iCH2CO, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  5.758714490E+00,  6.351240530E-03, -2.259553610E-06,  3.623215120E-10, -2.158555150E-14, -8.085334640E+03, -4.964904440E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  2.132411360E+00,  1.813194550E-02, -1.740933150E-05,  9.353360400E-09, -2.017248440E-12, -7.148085200E+03,  1.338079690E+01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.97*ATom, \
         /*   kbOveps = */ 1.0/436.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.0 \
                              } \
               }

// CH2CHO
#define iCH2CHO 29
#define CH2CHO { \
   /*      Name = */       (char*)("CH2CHO"), \
   /*         W = */       0.0120107*2+0.00100784*3+0.0159994*1, \
   /*       inx = */       iCH2CHO, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  5.916365350E+00,  8.846504260E-03, -3.149548950E-06,  5.054131890E-10, -3.013046210E-14, -1.047798920E+03, -6.106499810E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  2.668739560E+00,  9.623295380E-03,  1.606174380E-05, -2.876818200E-08,  1.250300660E-11,  2.194384290E+02,  1.256944760E+01 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.97*ATom, \
         /*   kbOveps = */ 1.0/436.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.0 \
                              } \
               }

// CH3CHO
#define iCH3CHO 30
#define CH3CHO { \
   /*      Name = */       (char*)("CH3CHO"), \
   /*         W = */       0.0120107*2+0.00100784*4+0.0159994*1, \
   /*       inx = */       iCH3CHO, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  5.404110800E+00,  1.172305900E-02, -4.226313700E-06,  6.837245100E-10, -4.098486300E-14, -2.259312200E+04, -3.480791700E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.729459500E+00, -3.193285800E-03,  4.753492100E-05, -5.745861100E-08,  2.193111200E-11, -2.157287800E+04,  4.103015900E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.97*ATom, \
         /*   kbOveps = */ 1.0/436.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.0 \
                              } \
               }

// CH3CO
#define iCH3CO 31
#define  CH3CO { \
   /*      Name = */       (char*)("CH3CO"), \
   /*         W = */       0.0120107*2+0.00100784*3+0.0159994*1, \
   /*       inx = */       iCH3CO, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  5.313716500E+00,  9.173779300E-03, -3.322038600E-06,  5.394745600E-10, -3.245236800E-14, -3.645041400E+03, -1.675755800E+00 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  4.035870500E+00,  8.772948700E-04,  3.071001000E-05, -3.924756500E-08,  1.529686900E-11, -2.682073800E+03,  7.861768200E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 3.97*ATom, \
         /*   kbOveps = */ 1.0/436.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.0 \
                              } \
               }

// H2CC
#define iH2CC 32
#define   H2CC { \
   /*      Name = */       (char*)("H2CC"), \
   /*         W = */       0.0120107*2+0.00100784*2, \
   /*       inx = */       iH2CC, \
   /*    cpCoeff = */       {  \
      /*     TSwitch1 = */          1000.0, \
      /*     TSwitch2 = */          6000.0, \
      /*         TMin = */          200.0, \
      /*         TMax = */          6000.0, \
      /*          cpM = */          {  0.000000000E+00,  0.000000000E+00,  4.278073050E+00,  4.756226260E-03, -1.630073780E-06,  2.546226800E-10, -1.488600860E-14,  4.801404780E+04,  6.399786000E-01 }, \
      /*          cpL = */          {  0.000000000E+00,  0.000000000E+00,  3.281549410E+00,  6.976426500E-03, -2.385279140E-06, -1.210776310E-09,  9.820417340E-13,  4.831917060E+04,  5.920356860E+00 }, \
                                }, \
      /* DiffCoeff = */       {  \
         /*      Geom = */ SpeciesGeom_NonLinear, \
         /*     sigma = */ 4.1*ATom, \
         /*   kbOveps = */ 1.0/209.0, \
         /*        mu = */ 0.0*DToCm, \
         /*     alpha = */ 0.0*ATom*ATom*ATom, \
         /*      Z298 = */ 2.5 \
                              } \
               }


//---------------------------------
// Define Reactions
//---------------------------------

// R 1: H + O2 <=> O + OH
#define R1 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.841000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   7.704293669e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          } \
           }

// R 2: O + H2 <=> H + OH
#define R2 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.848000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   4.000596647e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          } \
           }

// R 3: O + H2 <=> H + OH
#define R3 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.687000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   9.651753924e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          } \
           }

// R 4: OH + H2 <=> H + H2O
#define R4 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.256000000e+02, \
      /*           n = */   1.510000000e+00, \
      /*        EovR = */   1.729566123e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 5: 2 OH <=> O + H2O
#define R5 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.161000000e-02, \
      /*           n = */   2.420000000e+00, \
      /*        EovR = */   -9.702075894e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iOH , /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 6: H2 <=> 2 H
#define R6 { \
      /* ArrCoeff  = */   {  \
         /*           A = */   4.580000000e+13, \
         /*           n = */   -1.400000000e+00, \
         /*        EovR = */   5.253110491e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   8, \
   /*       educts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.95 }, \
      { /* ind = */ iCO2, /* eff = */ 3.83 }, \
      { /* ind = */ iH2 , /* eff = */ 2.55 }, \
      { /* ind = */ iH2O, /* eff = */ 12.02 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          } \
           }

// R 7: 2 O <=> O2
#define R7 { \
      /* ArrCoeff  = */   {  \
         /*           A = */   6.160000000e+03, \
         /*           n = */   -5.000000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   8, \
   /*       educts = */   {  \
      { /* ind = */ iO  , /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO2 , /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.9 }, \
      { /* ind = */ iCO2, /* eff = */ 3.8 }, \
      { /* ind = */ iH2 , /* eff = */ 2.5 }, \
      { /* ind = */ iH2O, /* eff = */ 12.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          } \
           }

// R 8: O + H <=> OH
#define R8 { \
      /* ArrCoeff  = */   {  \
         /*           A = */   4.710000000e+06, \
         /*           n = */   -1.000000000e+00, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   8, \
   /*       educts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 2.52 }, \
      { /* ind = */ iCO2, /* eff = */ 5.01 }, \
      { /* ind = */ iH2 , /* eff = */ 2.5 }, \
      { /* ind = */ iH2O, /* eff = */ 15.8 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          } \
           }

// R 9: H2O <=> H + OH
#define R9 { \
      /* ArrCoeff  = */   {  \
         /*           A = */   6.060000000e+21, \
         /*           n = */   -3.322000000e+00, \
         /*        EovR = */   6.078894025e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   9, \
   /*       educts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 2.4 }, \
      { /* ind = */ iCO2, /* eff = */ 4.67 }, \
      { /* ind = */ iH2 , /* eff = */ 3.77 }, \
      { /* ind = */ iH2O, /* eff = */ 0.0 }, \
      { /* ind = */ iO2 , /* eff = */ 1.5 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          } \
           }

// R 10: 2 H2O <=> H + OH + H2O
#define R10 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.528000000e+19, \
      /*           n = */   -2.440000000e+00, \
      /*        EovR = */   6.048700843e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   3, \
   /*       educts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 11: H + O2 (+ M) <=> HO2 (+ M)
#define R11 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   6.370000000e+08, \
         /*           n = */   -1.720000000e+00, \
         /*        EovR = */   2.641903446e+02, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   4.565000000e+06, \
         /*           n = */   4.400000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   9, \
   /*       educts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.9 }, \
      { /* ind = */ iCO2, /* eff = */ 3.45 }, \
      { /* ind = */ iH2 , /* eff = */ 1.87 }, \
      { /* ind = */ iH2O, /* eff = */ 15.81 }, \
      { /* ind = */ iO2 , /* eff = */ 0.75 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     5.000000000e-01, \
/*               T1 = */     9.000000000e+04, \
/*               T2 = */     9.000000000e+04, \
/*               T3 = */     3.000000000e+01  \
                       }} \
           }

// R 12: HO2 + H <=> H2 + O2
#define R12 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.945000000e+00, \
      /*           n = */   2.087000000e+00, \
      /*        EovR = */   -7.321846694e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          } \
           }

// R 13: HO2 + H <=> 2 OH
#define R13 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.888000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   1.509659112e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*       educts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          } \
           }

// R 14: HO2 + H <=> O + H2O
#define R14 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.632000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 15: HO2 + O <=> OH + O2
#define R15 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.609000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.239327683e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          } \
           }

// R 16: HO2 + OH <=> H2O + O2
#define R16 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.347000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -5.500191365e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          } \
           }

// R 17: HO2 + OH <=> H2O + O2
#define R17 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.534000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.500191365e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          } \
           }

// R 18: 2 HO2 <=> H2O2 + O2
#define R18 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.958000000e+05, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -7.090365630e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O2, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          } \
           }

// R 19: 2 HO2 <=> H2O2 + O2
#define R19 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.111000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.555545533e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O2, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          } \
           }

// R 20: H2O2 (+ M) <=> 2 OH (+ M)
#define R20 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   2.490000000e+18, \
         /*           n = */   -2.300000000e+00, \
         /*        EovR = */   2.453196057e+04, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   2.187000000e+12, \
         /*           n = */   9.000000000e-01, \
         /*        EovR = */   2.453196057e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   10, \
   /*       educts = */   {  \
      { /* ind = */ iH2O2, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.33 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 2.8 }, \
      { /* ind = */ iCO2, /* eff = */ 1.6 }, \
      { /* ind = */ iH2 , /* eff = */ 3.27 }, \
      { /* ind = */ iH2O, /* eff = */ 6.63 }, \
      { /* ind = */ iH2O2, /* eff = */ 6.61 }, \
      { /* ind = */ iO2 , /* eff = */ 1.2 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     5.800000000e-01, \
/*               T1 = */     9.000000000e+04, \
/*               T2 = */     9.000000000e+04, \
/*               T3 = */     3.000000000e+01  \
                       }} \
           }

// R 21: H2O2 + H <=> OH + H2O
#define R21 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.045000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   1.997782225e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iH2O2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 22: H2O2 + H <=> HO2 + H2
#define R22 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.856000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   4.000596647e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iH2O2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 23: H2O2 + O <=> OH + HO2
#define R23 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.513000000e+00, \
      /*           n = */   2.000000000e+00, \
      /*        EovR = */   1.997782225e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iH2O2, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          } \
           }

// R 24: H2O2 + OH <=> H2O + HO2
#define R24 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.565000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   1.600238659e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iH2O2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          } \
           }

// R 25: H2O2 + OH <=> H2O + HO2
#define R25 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.340000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   3.658407249e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iH2O2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          } \
           }

// R 26: CO + O (+ M) <=> CO2 (+ M)
#define R26 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   1.400000000e+09, \
         /*           n = */   -2.100000000e+00, \
         /*        EovR = */   2.767708372e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.880000000e+05, \
         /*           n = */   0.000000000e+00, \
         /*        EovR = */   1.222823881e+03, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   8, \
   /*       educts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCO2, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.9 }, \
      { /* ind = */ iCO2, /* eff = */ 3.8 }, \
      { /* ind = */ iH2 , /* eff = */ 2.5 }, \
      { /* ind = */ iH2O, /* eff = */ 12.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
   /*      Ftype = */     F_Lindemann, \
   /*     FOData = */     { .Lindemann = { \
   /*            dummy = */     0, \
                          } } \
           }

// R 27: CO + O2 <=> O + CO2
#define R27 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.533000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   2.400357988e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 28: CO + OH <=> H + CO2
#define R28 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.187000000e-02, \
      /*           n = */   2.053000000e+00, \
      /*        EovR = */   -1.791462146e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 29: CO + OH <=> H + CO2
#define R29 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.017000000e+06, \
      /*           n = */   -6.640000000e-01, \
      /*        EovR = */   1.670689417e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 30: CO + HO2 <=> OH + CO2
#define R30 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.570000000e-01, \
      /*           n = */   2.180000000e+00, \
      /*        EovR = */   9.029774370e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 31: HCO <=> H + CO
#define R31 { \
      /* ArrCoeff  = */   {  \
         /*           A = */   4.800000000e+11, \
         /*           n = */   -1.200000000e+00, \
         /*        EovR = */   8.924098232e+03, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   9, \
   /*       educts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 3.29 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.6 }, \
      { /* ind = */ iCO , /* eff = */ 2.04 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 1.31 }, \
      { /* ind = */ iH2O, /* eff = */ 15.31 }, \
      { /* ind = */ iO2 , /* eff = */ 1.32 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          } \
           }

// R 32: HCO + H <=> H2 + CO
#define R32 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.482000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 33: HCO + O <=> OH + CO
#define R33 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.010000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 34: HCO + O <=> H + CO2
#define R34 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.001000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 35: HCO + OH <=> H2O + CO
#define R35 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.199000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 36: HCO + O2 <=> HO2 + CO
#define R36 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.562000000e+04, \
      /*           n = */   5.210000000e-01, \
      /*        EovR = */   -2.621774658e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 37: C + OH <=> H + CO
#define R37 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC  , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 38: C + O2 <=> O + CO
#define R38 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.620000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   3.200477318e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC  , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 39: CH + H <=> C + H2
#define R39 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.089000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC  , /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 40: CH + O <=> H + CO
#define R40 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.700000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 41: CH + OH <=> H + HCO
#define R41 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 42: CH + H2 <=> H + CH2
#define R42 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.612000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   1.670689417e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 } \
                          } \
           }

// R 43: CH + H2 (+ M) <=> CH3 (+ M)
#define R43 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   2.430000000e+10, \
         /*           n = */   -1.600000000e+00, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   5.130000000e+07, \
         /*           n = */   1.500000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     5.140000000e-01, \
/*               T1 = */     2.285000000e+04, \
/*               T2 = */     1.035000000e+04, \
/*               T3 = */     1.520000000e+02  \
                       }} \
           }

// R 44: CH + H2O <=> H + CH2O
#define R44 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.430000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -4.448462184e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 45: CH + O2 <=> O + HCO
#define R45 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.840000000e+02, \
      /*           n = */   1.430000000e+00, \
      /*        EovR = */   6.038636449e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 46: CH + O2 <=> CO2 + H
#define R46 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.781000000e+02, \
      /*           n = */   1.430000000e+00, \
      /*        EovR = */   6.038636449e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCO2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          } \
           }

// R 47: CH + O2 <=> CO + OH
#define R47 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.840000000e+02, \
      /*           n = */   1.430000000e+00, \
      /*        EovR = */   6.038636449e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          } \
           }

// R 48: CH + O2 -> O + H + CO
#define R48 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.789000000e+02, \
      /*           n = */   1.430000000e+00, \
      /*        EovR = */   6.038636449e+02, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   2, \
   /*      Npducts = */   3, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 49: CH + CO (+ M) <=> HCCO (+ M)
#define R49 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   3.260000000e+12, \
         /*           n = */   -2.500000000e+00, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.020000000e+09, \
         /*           n = */   -4.000000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     4.000000000e-01, \
/*               T1 = */     9.000000000e+04, \
/*               T2 = */     9.000000000e+04, \
/*               T3 = */     3.000000000e+01  \
                       }} \
           }

// R 50: CH + CO2 <=> HCO + CO
#define R50 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.380000000e+01, \
      /*           n = */   1.510000000e+00, \
      /*        EovR = */   -3.598020884e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 51: CH2 + H (+ M) <=> CH3 (+ M)
#define R51 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   1.390000000e+22, \
         /*           n = */   -5.040000000e+00, \
         /*        EovR = */   3.723825810e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   2.130000000e+07, \
         /*           n = */   3.200000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     4.050000000e-01, \
/*               T1 = */     2.811000000e+03, \
/*               T2 = */     9.908000000e+03, \
/*               T3 = */     2.580000000e+02  \
                       }} \
           }

// R 52: CH2 + O -> 2 H + CO
#define R52 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 2 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 53: CH2 + OH <=> H + CH2O
#define R53 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.899000000e+07, \
      /*           n = */   1.200000000e-01, \
      /*        EovR = */   -8.152159206e+01, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 54: CH2 + OH <=> CH + H2O
#define R54 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.630000000e-01, \
      /*           n = */   2.020000000e+00, \
      /*        EovR = */   3.409816715e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 55: CH2 + HO2 <=> OH + CH2O
#define R55 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 56: CH2 + H2 <=> H + CH3
#define R56 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.265000000e+00, \
      /*           n = */   2.000000000e+00, \
      /*        EovR = */   3.638278460e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          } \
           }

// R 57: CH2 + O2 -> OH + H + CO
#define R57 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.643000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.032197041e+02, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   2, \
   /*      Npducts = */   3, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 58: CH2 + O2 -> 2 H + CO2
#define R58 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.844000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.032197041e+02, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 2 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 59: CH2 + O2 <=> O + CH2O
#define R59 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.600000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.032197041e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 60: CH2 + O2 <=> H2 + CO2
#define R60 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.836000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.032197041e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 61: CH2 + O2 <=> H2O + CO
#define R61 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.200000000e+05, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.032197041e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 62: CH2 + C <=> H + C2H
#define R62 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iC  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H, /* nu = */ 1 } \
                          } \
           }

// R 63: CH2 + CH <=> H + C2H2
#define R63 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iCH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 64: 2 CH2 -> 2 H + C2H2
#define R64 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.000000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.529881328e+03, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 2 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 65: 2 CH2 <=> H2 + H2CC
#define R65 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.600000000e+09, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   6.010456145e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iH2CC, /* nu = */ 1 } \
                          } \
           }

// R 66: CH2(S) + H <=> CH + H2
#define R66 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 67: CH2(S) + O -> 2 H + CO
#define R67 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 2 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 68: CH2(S) + OH <=> H + CH2O
#define R68 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 69: CH2(S) + H2 <=> CH3 + H
#define R69 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.291000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          } \
           }

// R 70: CH2(S) + O2 <=> CH2 + O2
#define R70 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.130000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          } \
           }

// R 71: CH2(S) + H2O (+ M) <=> CH3OH (+ M)
#define R71 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   1.680000000e+29, \
         /*           n = */   -7.192000000e+00, \
         /*        EovR = */   2.907100230e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   2.940000000e+06, \
         /*           n = */   5.300000000e-02, \
         /*        EovR = */   -9.546077786e+02, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     9.920000000e-01, \
/*               T1 = */     4.731000000e+04, \
/*               T2 = */     4.711000000e+04, \
/*               T3 = */     9.430000000e+02  \
                       }} \
           }

// R 72: CH2(S) + H2O <=> CH2 + H2O
#define R72 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.510000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.168876925e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 73: CH2(S) + H2O <=> H2 + CH2O
#define R73 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.670000000e+15, \
      /*           n = */   -3.134000000e+00, \
      /*        EovR = */   1.660625023e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 74: CH2(S) + H2O2 <=> OH + CH3O
#define R74 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.290000000e+08, \
      /*           n = */   -1.380000000e-01, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH2O2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH3O, /* nu = */ 1 } \
                          } \
           }

// R 75: CH2(S) + CO <=> CH2 + CO
#define R75 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.000000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 76: CH2(S) + CO2 <=> CH2 + CO2
#define R76 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.330000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 77: CH2(S) + CO2 <=> CO + CH2O
#define R77 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.620000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 78: HCO + H (+ M) <=> CH2O (+ M)
#define R78 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   4.190000000e+22, \
         /*           n = */   -5.533000000e+00, \
         /*        EovR = */   3.083730346e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.913000000e+08, \
         /*           n = */   -3.300000000e-02, \
         /*        EovR = */   -7.145719798e+01, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.84 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     7.820000000e-01, \
/*               T1 = */     2.755000000e+03, \
/*               T2 = */     6.570000000e+03, \
/*               T3 = */     2.710000000e+02  \
                       }} \
           }

// R 79: CH2O (+ M) <=> H2 + CO (+ M)
#define R79 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   4.400000000e+32, \
         /*           n = */   -6.100000000e+00, \
         /*        EovR = */   4.730265218e+04, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   3.700000000e+13, \
         /*           n = */   0.000000000e+00, \
         /*        EovR = */   3.621974142e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     9.320000000e-01, \
/*               T1 = */     1.540000000e+03, \
/*               T2 = */     1.030000000e+04, \
/*               T3 = */     1.970000000e+02  \
                       }} \
           }

// R 80: CH2O + H <=> HCO + H2
#define R80 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.149000000e+01, \
      /*           n = */   1.900000000e+00, \
      /*        EovR = */   1.379828429e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 81: CH2O + O <=> OH + HCO
#define R81 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.244000000e+05, \
      /*           n = */   5.700000000e-01, \
      /*        EovR = */   1.389892823e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 82: CH2O + OH <=> HCO + H2O
#define R82 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.338000000e+01, \
      /*           n = */   1.630000000e+00, \
      /*        EovR = */   -5.308967878e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 83: CH2O + O2 <=> HO2 + HCO
#define R83 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.297000000e-01, \
      /*           n = */   2.500000000e+00, \
      /*        EovR = */   1.834739041e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 84: CH2O + HO2 <=> HCO + H2O2
#define R84 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.111000000e-02, \
      /*           n = */   2.500000000e+00, \
      /*        EovR = */   5.137873178e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iH2O2, /* nu = */ 1 } \
                          } \
           }

// R 85: CH2O + CH <=> H + CH2CO
#define R85 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.640000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.601645870e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iCH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2CO, /* nu = */ 1 } \
                          } \
           }

// R 86: CH2O + CH2 <=> CH3 + HCO
#define R86 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.400000000e-08, \
      /*           n = */   4.210000000e+00, \
      /*        EovR = */   5.636060686e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 87: CH2O + CH2(S) <=> CH3 + HCO
#define R87 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.330000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.767708372e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iCH2_S, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 88: CH2O + C2H <=> C2H2 + HCO
#define R88 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.400000000e-03, \
      /*           n = */   2.810000000e+00, \
      /*        EovR = */   2.949873905e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iC2H, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 89: CH2O + C2H3 <=> C2H4 + HCO
#define R89 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.400000000e-03, \
      /*           n = */   2.810000000e+00, \
      /*        EovR = */   2.949873905e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iC2H3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 90: CH3 + H (+ M) <=> CH4 (+ M)
#define R90 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   7.930000000e+12, \
         /*           n = */   -2.170000000e+00, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.801000000e+08, \
         /*           n = */   0.000000000e+00, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   8, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 0.89 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 3.42 }, \
      { /* ind = */ iO2 , /* eff = */ 0.59 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     1.240000000e-01, \
/*               T1 = */     3.310000000e+01, \
/*               T2 = */     9.000000000e+04, \
/*               T3 = */     1.801000000e+03  \
                       }} \
           }

// R 91: CH3 + O <=> H + CH2O
#define R91 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.722000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 92: CH3 + O -> H + H2 + CO
#define R92 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.384000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   2, \
   /*      Npducts = */   3, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 93: CH3 + OH (+ M) <=> CH3OH (+ M)
#define R93 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   7.240000000e+24, \
         /*           n = */   -6.000000000e+00, \
         /*        EovR = */   1.623386765e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   6.210000000e+07, \
         /*           n = */   -1.800000000e-02, \
         /*        EovR = */   -1.660625023e+01, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     1.855000000e-01, \
/*               T1 = */     1.675000000e+03, \
/*               T2 = */     4.530000000e+03, \
/*               T3 = */     1.560000000e+02  \
                       }} \
           }

// R 94: CH3 + OH <=> CH2 + H2O
#define R94 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.464000000e-02, \
      /*           n = */   2.570000000e+00, \
      /*        EovR = */   2.011872377e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 95: CH3 + OH <=> CH2(S) + H2O
#define R95 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.810000000e+09, \
      /*           n = */   -9.100000000e-01, \
      /*        EovR = */   2.747579584e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 96: CH3 + OH <=> H2 + CH2O
#define R96 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.735000000e+03, \
      /*           n = */   7.340000000e-01, \
      /*        EovR = */   -1.095509296e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 97: CH3 + HO2 <=> O2 + CH4
#define R97 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.269000000e-01, \
      /*           n = */   2.228000000e+00, \
      /*        EovR = */   -1.520729946e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO2 , /* nu = */ 1 }, \
      { /* ind = */ iCH4, /* nu = */ 1 } \
                          } \
           }

// R 98: CH3 + HO2 <=> OH + CH3O
#define R98 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.821000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.968996254e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH3O, /* nu = */ 1 } \
                          } \
           }

// R 99: CH3 + O2 <=> O + CH3O
#define R99 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.104000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   1.423960797e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iO  , /* nu = */ 1 }, \
      { /* ind = */ iCH3O, /* nu = */ 1 } \
                          } \
           }

// R 100: CH3 + O2 <=> OH + CH2O
#define R100 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.977000000e-05, \
      /*           n = */   2.860000000e+00, \
      /*        EovR = */   4.915450069e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 101: CH3 + C <=> H + C2H2
#define R101 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iC  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 102: CH3 + CH <=> H + C2H3
#define R102 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.062000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H3, /* nu = */ 1 } \
                          } \
           }

// R 103: CH3 + CH2 <=> H + C2H4
#define R103 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.824000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H4, /* nu = */ 1 } \
                          } \
           }

// R 104: CH3 + CH2(S) <=> H + C2H4
#define R104 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.400000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.501001929e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH2_S, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H4, /* nu = */ 1 } \
                          } \
           }

// R 105: 2 CH3 (+ M) <=> C2H6 (+ M)
#define R105 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   1.770000000e+38, \
         /*           n = */   -9.670000000e+00, \
         /*        EovR = */   3.130026559e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.844000000e+10, \
         /*           n = */   -9.700000000e-01, \
         /*        EovR = */   3.119962165e+02, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   8, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 1.99 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ iO2 , /* eff = */ 1.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     5.325000000e-01, \
/*               T1 = */     1.038000000e+03, \
/*               T2 = */     4.970000000e+03, \
/*               T3 = */     1.510000000e+02  \
                       }} \
           }

// R 106: 2 CH3 <=> H + C2H5
#define R106 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.621000000e+06, \
      /*           n = */   1.000000000e-01, \
      /*        EovR = */   5.334128863e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H5, /* nu = */ 1 } \
                          } \
           }

// R 107: CH3 + HCO <=> CH4 + CO
#define R107 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.300000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 108: CH3 + CH2O <=> HCO + CH4
#define R108 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.213000000e-05, \
      /*           n = */   3.360000000e+00, \
      /*        EovR = */   2.168876925e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iCH4, /* nu = */ 1 } \
                          } \
           }

// R 109: CH3O (+ M) <=> H + CH2O (+ M)
#define R109 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   6.020000000e+10, \
         /*           n = */   -5.470000000e-01, \
         /*        EovR = */   9.070031946e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.130000000e+10, \
         /*           n = */   1.210000000e+00, \
         /*        EovR = */   1.211501438e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     3.410000000e-01, \
/*               T1 = */     1.000000000e+03, \
/*               T2 = */     2.339000000e+03, \
/*               T3 = */     2.800000000e+01  \
                       }} \
           }

// R 110: CH3O + H (+ M) <=> CH3OH (+ M)
#define R110 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   6.700000000e+28, \
         /*           n = */   -7.380000000e+00, \
         /*        EovR = */   4.618047224e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   2.440000000e+05, \
         /*           n = */   7.600000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     6.840000000e-01, \
/*               T1 = */     4.149000000e+04, \
/*               T2 = */     3.980000000e+03, \
/*               T3 = */     3.705000000e+04  \
                       }} \
           }

// R 111: CH3O + H <=> H + CH2OH
#define R111 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.290000000e+01, \
      /*           n = */   1.820000000e+00, \
      /*        EovR = */   -3.537634520e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2OH, /* nu = */ 1 } \
                          } \
           }

// R 112: CH3O + H <=> H2 + CH2O
#define R112 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.790000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   2.999189436e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 113: CH3O + H <=> OH + CH3
#define R113 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.880000000e+08, \
      /*           n = */   -2.640000000e-01, \
      /*        EovR = */   -1.308371231e+01, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          } \
           }

// R 114: CH3O + H <=> CH2(S) + H2O
#define R114 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.970000000e+05, \
      /*           n = */   4.140000000e-01, \
      /*        EovR = */   1.222823881e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 115: CH3O + O <=> OH + CH2O
#define R115 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.780000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 116: CH3O + OH <=> H2O + CH2O
#define R116 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.810000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 117: CH3O + O2 <=> HO2 + CH2O
#define R117 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.320000000e+04, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   1.309880890e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 118: CH3O + CH3 <=> CH4 + CH2O
#define R118 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.400000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 119: CH3O + CO <=> CH3 + CO2
#define R119 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.000000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.535416745e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 120: CH2OH (+ M) <=> H + CH2O (+ M)
#define R120 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   3.010000000e+07, \
         /*           n = */   1.840000000e-01, \
         /*        EovR = */   8.670475501e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   7.370000000e+10, \
         /*           n = */   8.110000000e-01, \
         /*        EovR = */   1.991743589e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 5.97 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     1.000000000e-03, \
/*               T1 = */     6.000000000e+02, \
/*               T2 = */     2.780000000e+03, \
/*               T3 = */     5.000000000e+01  \
                       }} \
           }

// R 121: CH2OH + H (+ M) <=> CH3OH (+ M)
#define R121 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   1.340000000e+29, \
         /*           n = */   -7.380000000e+00, \
         /*        EovR = */   4.618047224e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   6.670000000e+04, \
         /*           n = */   9.600000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     6.840000000e-01, \
/*               T1 = */     4.149000000e+04, \
/*               T2 = */     3.980000000e+03, \
/*               T3 = */     3.705000000e+04  \
                       }} \
           }

// R 122: CH2OH + H <=> H2 + CH2O
#define R122 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.440000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 123: CH2OH + H <=> OH + CH3
#define R123 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.006000000e+07, \
      /*           n = */   1.980000000e-01, \
      /*        EovR = */   -1.212759487e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          } \
           }

// R 124: CH2OH + H <=> CH2(S) + H2O
#define R124 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.280000000e+05, \
      /*           n = */   5.160000000e-01, \
      /*        EovR = */   1.081922364e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 125: CH2OH + O <=> OH + CH2O
#define R125 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.030000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 126: CH2OH + OH <=> H2O + CH2O
#define R126 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.410000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 127: CH2OH + O2 <=> HO2 + CH2O
#define R127 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.298000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   1.880028814e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 128: CH2OH + CH3 <=> CH4 + CH2O
#define R128 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.400000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 129: CH4 + H <=> CH3 + H2
#define R129 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.781000000e-01, \
      /*           n = */   2.500000000e+00, \
      /*        EovR = */   4.824870523e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 130: CH4 + O <=> OH + CH3
#define R130 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.786000000e+02, \
      /*           n = */   1.560000000e+00, \
      /*        EovR = */   4.269819189e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          } \
           }

// R 131: CH4 + OH <=> CH3 + H2O
#define R131 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.839000000e-01, \
      /*           n = */   2.182000000e+00, \
      /*        EovR = */   1.230875396e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 132: CH4 + HO2 <=> CH3 + H2O2
#define R132 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.778000000e-02, \
      /*           n = */   2.500000000e+00, \
      /*        EovR = */   1.056761379e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iH2O2, /* nu = */ 1 } \
                          } \
           }

// R 133: CH4 + CH <=> H + C2H4
#define R133 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -1.997782225e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iCH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H4, /* nu = */ 1 } \
                          } \
           }

// R 134: CH4 + CH2 <=> 2 CH3
#define R134 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.483000000e+00, \
      /*           n = */   2.000000000e+00, \
      /*        EovR = */   4.161626953e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*       educts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          } \
           }

// R 135: CH4 + CH2(S) <=> 2 CH3
#define R135 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.867000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.501001929e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*       educts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iCH2_S, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          } \
           }

// R 136: CH4 + C2H <=> CH3 + C2H2
#define R136 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.300000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   3.019318224e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iC2H, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 137: CH3OH + H <=> CH2OH + H2
#define R137 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.550000000e+00, \
      /*           n = */   2.351000000e+00, \
      /*        EovR = */   2.975034890e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 138: CH3OH + H <=> CH3O + H2
#define R138 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.490000000e+00, \
      /*           n = */   2.147000000e+00, \
      /*        EovR = */   5.602848185e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 139: CH3OH + O <=> OH + CH2OH
#define R139 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.470000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   2.670083750e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH2OH, /* nu = */ 1 } \
                          } \
           }

// R 140: CH3OH + O <=> OH + CH3O
#define R140 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.200000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   4.549106125e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH3O, /* nu = */ 1 } \
                          } \
           }

// R 141: CH3OH + OH <=> CH2OH + H2O
#define R141 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.420000000e-01, \
      /*           n = */   2.370000000e+00, \
      /*        EovR = */   -4.857076584e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 142: CH3OH + OH <=> CH3O + H2O
#define R142 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.600000000e-02, \
      /*           n = */   2.700000000e+00, \
      /*        EovR = */   2.682161023e+01, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 143: CH3OH + O2 <=> CH2OH + HO2
#define R143 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.580000000e-01, \
      /*           n = */   2.270000000e+00, \
      /*        EovR = */   2.151767455e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          } \
           }

// R 144: CH3OH + HO2 <=> CH2OH + H2O2
#define R144 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.280000000e-11, \
      /*           n = */   5.060000000e+00, \
      /*        EovR = */   5.139382838e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iH2O2, /* nu = */ 1 } \
                          } \
           }

// R 145: CH3OH + HO2 <=> CH3O + H2O2
#define R145 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.340000000e-08, \
      /*           n = */   4.120000000e+00, \
      /*        EovR = */   8.168765456e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iH2O2, /* nu = */ 1 } \
                          } \
           }

// R 146: CH3OH + CH <=> CH3 + CH2O
#define R146 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.040000000e+12, \
      /*           n = */   -1.930000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iCH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 147: CH3OH + CH2 <=> CH3 + CH2OH
#define R147 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.200000000e-05, \
      /*           n = */   3.200000000e+00, \
      /*        EovR = */   3.610601377e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH2OH, /* nu = */ 1 } \
                          } \
           }

// R 148: CH3OH + CH2 <=> CH3 + CH3O
#define R148 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.450000000e-05, \
      /*           n = */   3.100000000e+00, \
      /*        EovR = */   3.492344746e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH3O, /* nu = */ 1 } \
                          } \
           }

// R 149: CH3OH + CH2(S) <=> CH3 + CH3O
#define R149 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.000000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.767708372e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iCH2_S, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH3O, /* nu = */ 1 } \
                          } \
           }

// R 150: CH3OH + CH2(S) <=> CH3 + CH2OH
#define R150 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -2.767708372e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iCH2_S, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH2OH, /* nu = */ 1 } \
                          } \
           }

// R 151: CH3OH + CH3 <=> CH2OH + CH4
#define R151 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.650000000e-04, \
      /*           n = */   3.030000000e+00, \
      /*        EovR = */   4.388075819e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iCH4, /* nu = */ 1 } \
                          } \
           }

// R 152: CH3OH + CH3 <=> CH3O + CH4
#define R152 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.150000000e-02, \
      /*           n = */   2.270000000e+00, \
      /*        EovR = */   4.383043622e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3O, /* nu = */ 1 }, \
      { /* ind = */ iCH4, /* nu = */ 1 } \
                          } \
           }

// R 153: CH3OH + C2H <=> C2H2 + CH2OH
#define R153 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.000000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iC2H, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iCH2OH, /* nu = */ 1 } \
                          } \
           }

// R 154: CH3OH + C2H <=> C2H2 + CH3O
#define R154 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.200000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iC2H, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iCH3O, /* nu = */ 1 } \
                          } \
           }

// R 155: CH3OH + C2H3 <=> C2H4 + CH2OH
#define R155 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.200000000e-05, \
      /*           n = */   3.200000000e+00, \
      /*        EovR = */   3.610601377e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iC2H3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iCH2OH, /* nu = */ 1 } \
                          } \
           }

// R 156: CH3OH + C2H3 <=> C2H4 + CH3O
#define R156 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.450000000e-05, \
      /*           n = */   3.100000000e+00, \
      /*        EovR = */   3.492344746e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3OH, /* nu = */ 1 }, \
      { /* ind = */ iC2H3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iCH3O, /* nu = */ 1 } \
                          } \
           }

// R 157: C2H + H (+ M) <=> C2H2 (+ M)
#define R157 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   3.750000000e+21, \
         /*           n = */   -4.800000000e+00, \
         /*        EovR = */   9.561174377e+02, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   2.250000000e+07, \
         /*           n = */   3.200000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iC2H, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     6.460000000e-01, \
/*               T1 = */     1.315000000e+03, \
/*               T2 = */     5.566000000e+03, \
/*               T3 = */     1.320000000e+02  \
                       }} \
           }

// R 158: C2H + O <=> CH + CO
#define R158 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.400000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 159: C2H + OH <=> H + HCCO
#define R159 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iHCCO, /* nu = */ 1 } \
                          } \
           }

// R 160: C2H + H2 <=> H + C2H2
#define R160 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.110000000e+00, \
      /*           n = */   2.320000000e+00, \
      /*        EovR = */   4.438397790e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 161: C2H + O2 <=> HCO + CO
#define R161 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.630000000e+08, \
      /*           n = */   -3.500000000e-01, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 162: HCCO + H <=> CH2(S) + CO
#define R162 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.320000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2_S, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 163: HCCO + O <=> H + 2 CO
#define R163 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.730000000e+08, \
      /*           n = */   -1.120000000e-01, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 2 } \
                          } \
           }

// R 164: HCCO + O <=> CH + CO2
#define R164 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.950000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.600835306e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH , /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 165: HCCO + O2 <=> OH + 2 CO
#define R165 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.567000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   4.297496273e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 2 } \
                          } \
           }

// R 166: HCCO + CH <=> CO + C2H2
#define R166 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ iCH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 167: HCCO + CH2 <=> C2H3 + CO
#define R167 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 168: 2 HCCO <=> 2 CO + C2H2
#define R168 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCO , /* nu = */ 2 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 169: C2H2 (+ M) <=> H2CC (+ M)
#define R169 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   2.450000000e+09, \
         /*           n = */   -6.400000000e-01, \
         /*        EovR = */   2.501001929e+04, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   8.000000000e+14, \
         /*           n = */   -5.200000000e-01, \
         /*        EovR = */   2.553839998e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2CC, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
   /*      Ftype = */     F_Lindemann, \
   /*     FOData = */     { .Lindemann = { \
   /*            dummy = */     0, \
                          } } \
           }

// R 170: C2H2 + H (+ M) <=> C2H3 (+ M)
#define R170 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   3.630000000e+15, \
         /*           n = */   -3.380000000e+00, \
         /*        EovR = */   4.262270893e+02, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   5.540000000e+02, \
         /*           n = */   1.640000000e+00, \
         /*        EovR = */   1.054748500e+03, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     2.150000000e-01, \
/*               T1 = */     1.043000000e+03, \
/*               T2 = */     2.341000000e+03, \
/*               T3 = */     1.070000000e+01  \
                       }} \
           }

// R 171: C2H2 + O <=> H + HCCO
#define R171 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.679000000e+02, \
      /*           n = */   1.400000000e+00, \
      /*        EovR = */   1.110102667e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iHCCO, /* nu = */ 1 } \
                          } \
           }

// R 172: C2H2 + O <=> CO + CH2
#define R172 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.304000000e+02, \
      /*           n = */   1.400000000e+00, \
      /*        EovR = */   1.110102667e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 } \
                          } \
           }

// R 173: C2H2 + OH <=> H + CH2CO
#define R173 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.670000000e-07, \
      /*           n = */   3.566000000e+00, \
      /*        EovR = */   -1.192630699e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2CO, /* nu = */ 1 } \
                          } \
           }

// R 174: C2H2 + OH <=> C2H + H2O
#define R174 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.630000000e+00, \
      /*           n = */   2.140000000e+00, \
      /*        EovR = */   8.584928151e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 175: C2H2 + OH <=> CH3 + CO
#define R175 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.140000000e-01, \
      /*           n = */   1.620000000e+00, \
      /*        EovR = */   -3.678536037e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 176: H2CC + H <=> C2H2 + H
#define R176 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iH2CC, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          } \
           }

// R 177: H2CC + OH <=> CH2CO + H
#define R177 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iH2CC, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          } \
           }

// R 178: H2CC + O2 <=> 2 HCO
#define R178 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.124000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*       educts = */   {  \
      { /* ind = */ iH2CC, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          } \
           }

// R 179: CH2 + CO (+ M) <=> CH2CO (+ M)
#define R179 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   2.690000000e+21, \
         /*           n = */   -5.110000000e+00, \
         /*        EovR = */   3.570343800e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   8.100000000e+05, \
         /*           n = */   5.000000000e-01, \
         /*        EovR = */   2.269520865e+03, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     5.910000000e-01, \
/*               T1 = */     1.226000000e+03, \
/*               T2 = */     5.185000000e+03, \
/*               T3 = */     2.750000000e+02  \
                       }} \
           }

// R 180: CH2CO + H <=> HCCO + H2
#define R180 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.200000000e+01, \
      /*           n = */   1.900000000e+00, \
      /*        EovR = */   5.963153493e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 181: CH2CO + H <=> CH3 + CO
#define R181 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.676000000e+02, \
      /*           n = */   1.450000000e+00, \
      /*        EovR = */   1.398950777e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 182: CH2CO + O <=> OH + HCCO
#define R182 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   5.183162952e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iHCCO, /* nu = */ 1 } \
                          } \
           }

// R 183: CH2CO + O <=> CH2 + CO2
#define R183 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.080000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   6.798498202e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 184: CH2CO + O <=> 2 HCO
#define R184 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.610000000e+05, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   6.798498202e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 2 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          } \
           }

// R 185: CH2CO + O <=> CO + CH2O
#define R185 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.610000000e+05, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   6.798498202e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 186: CH2CO + OH <=> HCCO + H2O
#define R186 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.120000000e-02, \
      /*           n = */   2.740000000e+00, \
      /*        EovR = */   1.117147743e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCCO, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 187: CH2CO + OH <=> CH3 + CO2
#define R187 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.800000000e+05, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -5.097615602e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 188: CH2CO + OH <=> CH2OH + CO
#define R188 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.010000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -5.097615602e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2OH, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 189: CH2CO + CH <=> C2H3 + CO
#define R189 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.450000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iCH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          } \
           }

// R 190: C2H3 + H (+ M) <=> C2H4 (+ M)
#define R190 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   1.400000000e+18, \
         /*           n = */   -3.860000000e+00, \
         /*        EovR = */   1.670689417e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   3.880000000e+07, \
         /*           n = */   2.000000000e-01, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     7.820000000e-01, \
/*               T1 = */     2.663000000e+03, \
/*               T2 = */     6.095000000e+03, \
/*               T3 = */     2.075000000e+02  \
                       }} \
           }

// R 191: C2H3 + H <=> H2 + C2H2
#define R191 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.210000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 192: C2H3 + H <=> H2CC + H2
#define R192 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.893000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2CC, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 193: C2H3 + O <=> H + CH2CO
#define R193 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.010000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2CO, /* nu = */ 1 } \
                          } \
           }

// R 194: C2H3 + OH <=> H2O + C2H2
#define R194 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.100000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 195: C2H3 + OH <=> CH3 + HCO
#define R195 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.000000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 196: C2H3 + OH <=> CH3CO + H
#define R196 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          } \
           }

// R 197: C2H3 + O2 <=> HCO + CH2O
#define R197 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.936000000e+09, \
      /*           n = */   -9.590000000e-01, \
      /*        EovR = */   2.918674284e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 198: C2H3 + O2 <=> CH2CHO + O
#define R198 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.849000000e+03, \
      /*           n = */   9.230000000e-01, \
      /*        EovR = */   1.137276531e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          } \
           }

// R 199: C2H3 + O2 <=> C2H2 + HO2
#define R199 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.400000000e-05, \
      /*           n = */   2.950000000e+00, \
      /*        EovR = */   9.359886496e+01, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H2, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          } \
           }

// R 200: C2H3 + CH3 <=> CH4 + C2H2
#define R200 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.000000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -3.849630736e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iC2H2, /* nu = */ 1 } \
                          } \
           }

// R 201: CH2CHO (+ M) <=> CH2CO + H (+ M)
#define R201 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   2.440000000e+23, \
         /*           n = */   -3.790000000e+00, \
         /*        EovR = */   2.192880504e+04, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.430000000e+15, \
         /*           n = */   -1.500000000e-01, \
         /*        EovR = */   2.294983782e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   10, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H2, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H4, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     7.960000000e-01, \
/*               T1 = */     5.000000000e+04, \
/*               T2 = */     3.420400000e+04, \
/*               T3 = */     1.000000000e+02  \
                       }} \
           }

// R 202: CH2CHO (+ M) <=> CH3 + CO (+ M)
#define R202 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   2.340000000e+21, \
         /*           n = */   -3.180000000e+00, \
         /*        EovR = */   1.683018300e+04, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   2.930000000e+12, \
         /*           n = */   2.900000000e-01, \
         /*        EovR = */   2.029283779e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   10, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H2, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H4, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     2.110000000e-01, \
/*               T1 = */     2.032000000e+03, \
/*               T2 = */     1.117020000e+05, \
/*               T3 = */     1.990000000e+02  \
                       }} \
           }

// R 203: CH2CHO + H <=> CH3 + HCO
#define R203 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.200000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 204: CH2CHO + H <=> CH2CO + H2
#define R204 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.100000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 205: CH2CHO + H <=> CH3CO + H
#define R205 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.200000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          } \
           }

// R 206: CH2CHO + O -> H + CH2 + CO2
#define R206 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.580000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   2, \
   /*      Npducts = */   3, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 207: CH2CHO + OH <=> H2O + CH2CO
#define R207 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.200000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2O, /* nu = */ 1 }, \
      { /* ind = */ iCH2CO, /* nu = */ 1 } \
                          } \
           }

// R 208: CH2CHO + OH <=> HCO + CH2OH
#define R208 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.010000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHCO, /* nu = */ 1 }, \
      { /* ind = */ iCH2OH, /* nu = */ 1 } \
                          } \
           }

// R 209: CH2CHO + O2 -> OH + CO + CH2O
#define R209 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.300000000e+04, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   false, \
   /*      Neducts = */   2, \
   /*      Npducts = */   3, \
   /*       educts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 210: CH3CO (+ M) <=> CH3 + CO (+ M)
#define R210 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   5.650000000e+12, \
         /*           n = */   -9.700000000e-01, \
         /*        EovR = */   7.339459384e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.070000000e+12, \
         /*           n = */   6.300000000e-01, \
         /*        EovR = */   8.501896900e+03, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   10, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H2, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H4, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     3.600000000e-01, \
/*               T1 = */     5.000000000e+04, \
/*               T2 = */     1.693500000e+04, \
/*               T3 = */     1.220000000e+02  \
                       }} \
           }

// R 211: CH3CO + H (+ M) <=> CH3CHO (+ M)
#define R211 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   3.850000000e+32, \
         /*           n = */   -8.569000000e+00, \
         /*        EovR = */   2.767708372e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   9.600000000e+07, \
         /*           n = */   0.000000000e+00, \
         /*        EovR = */   0.000000000e+00, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   10, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H2, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H4, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     1.000000000e+00, \
/*               T1 = */     2.900000000e+03, \
/*               T2 = */     5.132000000e+03, \
/*               T3 = */     2.900000000e+03  \
                       }} \
           }

// R 212: CH3CO + H <=> CH3 + HCO
#define R212 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.600000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 213: CH3CO + O <=> CH2CO + OH
#define R213 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.270000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          } \
           }

// R 214: CH3CO + O <=> CH3 + CO2
#define R214 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.580000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 } \
                          } \
           }

// R 215: CH3CO + OH <=> CH2CO + H2O
#define R215 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.200000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2CO, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 216: CH3CO + OH <=> CH3 + CO + OH
#define R216 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   3, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          } \
           }

// R 217: CH3CO + HO2 <=> CH3 + CO2 + OH
#define R217 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.000000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   3, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCO2, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          } \
           }

// R 218: CH3CO + O2 <=> HO2 + CH2CO
#define R218 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.300000000e+04, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iCH2CO, /* nu = */ 1 } \
                          } \
           }

// R 219: CH3CO + CH3 <=> CH4 + CH2CO
#define R219 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.080000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iCH2CO, /* nu = */ 1 } \
                          } \
           }

// R 220: CH3CHO (+ M) <=> CH4 + CO (+ M)
#define R220 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   2.290000000e+52, \
         /*           n = */   -1.130000000e+01, \
         /*        EovR = */   4.826984045e+04, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   5.440000000e+21, \
         /*           n = */   -1.740000000e+00, \
         /*        EovR = */   4.346006652e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   10, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iCO , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H2, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H4, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 } \
                          }, \
/*      Ftype = */     F_SRI, \
/*     FOData = */     { .SRI = { \
/*                A = */     1.380000000e-01, \
/*                B = */     -6.700000000e+02, \
/*                C = */     1.000000000e-03, \
/*                D = */     1.000000000e+00,  \
/*                E = */     0.000000000e+00  \
                       }} \
           }

// R 221: CH3CHO (+ M) <=> CH3 + HCO (+ M)
#define R221 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   9.150000000e+52, \
         /*           n = */   -1.130000000e+01, \
         /*        EovR = */   4.826984045e+04, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   2.180000000e+22, \
         /*           n = */   -1.740000000e+00, \
         /*        EovR = */   4.346006652e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   10, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H2, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H4, /* eff = */ 3.0 }, \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2 , /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 } \
                          }, \
/*      Ftype = */     F_SRI, \
/*     FOData = */     { .SRI = { \
/*                A = */     1.380000000e-01, \
/*                B = */     -6.700000000e+02, \
/*                C = */     1.000000000e-03, \
/*                D = */     1.000000000e+00,  \
/*                E = */     0.000000000e+00  \
                       }} \
           }

// R 222: CH3CHO + H <=> CH2CHO + H2
#define R222 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.050000000e+03, \
      /*           n = */   1.160000000e+00, \
      /*        EovR = */   1.210243388e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2CHO, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 223: CH3CHO + H <=> CH3CO + H2
#define R223 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.050000000e+03, \
      /*           n = */   1.160000000e+00, \
      /*        EovR = */   1.210243388e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 224: CH3CHO + O <=> OH + CH2CHO
#define R224 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.920000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   9.098212249e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH2CHO, /* nu = */ 1 } \
                          } \
           }

// R 225: CH3CHO + O <=> OH + CH3CO
#define R225 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.920000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   9.098212249e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iCH3CO, /* nu = */ 1 } \
                          } \
           }

// R 226: CH3CHO + OH <=> CH3CO + H2O
#define R226 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.690000000e+02, \
      /*           n = */   1.350000000e+00, \
      /*        EovR = */   -7.920678142e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 227: CH3CHO + O2 <=> HO2 + CH3CO
#define R227 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.200000000e-01, \
      /*           n = */   2.500000000e+00, \
      /*        EovR = */   1.890093208e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iCH3CO, /* nu = */ 1 } \
                          } \
           }

// R 228: CH3CHO + HO2 <=> CH3CO + H2O2
#define R228 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.100000000e-02, \
      /*           n = */   2.500000000e+00, \
      /*        EovR = */   5.132840981e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iH2O2, /* nu = */ 1 } \
                          } \
           }

// R 229: CH3CHO + CH3 <=> CH3CO + CH4
#define R229 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.720000000e+00, \
      /*           n = */   1.770000000e+00, \
      /*        EovR = */   2.979060648e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iCH3CHO, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3CO, /* nu = */ 1 }, \
      { /* ind = */ iCH4, /* nu = */ 1 } \
                          } \
           }

// R 230: C2H4 (+ M) <=> H2 + H2CC (+ M)
#define R230 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   3.710000000e+10, \
         /*           n = */   0.000000000e+00, \
         /*        EovR = */   3.412634745e+04, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   3.985000000e+15, \
         /*           n = */   0.000000000e+00, \
         /*        EovR = */   4.381030744e+04, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   1, \
   /*      Npducts = */   2, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iH2CC, /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.01 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
   /*      Ftype = */     F_Lindemann, \
   /*     FOData = */     { .Lindemann = { \
   /*            dummy = */     0, \
                          } } \
           }

// R 231: C2H4 + H (+ M) <=> C2H5 (+ M)
#define R231 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   2.900000000e+27, \
         /*           n = */   -6.642000000e+00, \
         /*        EovR = */   2.903074473e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   1.232000000e+03, \
         /*           n = */   1.463000000e+00, \
         /*        EovR = */   6.818626990e+02, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 4.92 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     1.569000000e+00, \
/*               T1 = */     2.990000000e+02, \
/*               T2 = */     1.524000000e+02, \
/*               T3 = */     -9.147000000e+03  \
                       }} \
           }

// R 232: C2H4 + H <=> C2H3 + H2
#define R232 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.201000000e-04, \
      /*           n = */   3.620000000e+00, \
      /*        EovR = */   5.671286065e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 233: C2H4 + O <=> CH3 + HCO
#define R233 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.355000000e+00, \
      /*           n = */   1.880000000e+00, \
      /*        EovR = */   9.208920584e+01, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 234: C2H4 + O <=> H + CH2CHO
#define R234 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.700000000e+03, \
      /*           n = */   9.070000000e-01, \
      /*        EovR = */   4.222013317e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH2CHO, /* nu = */ 1 } \
                          } \
           }

// R 235: C2H4 + O <=> CH2 + CH2O
#define R235 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.400000000e-02, \
      /*           n = */   2.620000000e+00, \
      /*        EovR = */   2.309778442e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 236: C2H4 + OH <=> C2H3 + H2O
#define R236 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.144000000e-02, \
      /*           n = */   2.745000000e+00, \
      /*        EovR = */   1.115134864e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 237: C2H4 + OH <=> CH2O + CH3
#define R237 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.780000000e-01, \
      /*           n = */   1.680000000e+00, \
      /*        EovR = */   1.036632590e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH2O, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          } \
           }

// R 238: C2H4 + OH <=> H + CH3CHO
#define R238 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.380000000e-08, \
      /*           n = */   3.910000000e+00, \
      /*        EovR = */   8.670475501e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH3CHO, /* nu = */ 1 } \
                          } \
           }

// R 239: C2H4 + OH <=> H + CH3CHO
#define R239 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.190000000e-01, \
      /*           n = */   2.190000000e+00, \
      /*        EovR = */   2.644922765e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH3CHO, /* nu = */ 1 } \
                          } \
           }

// R 240: C2H4 + CH3 <=> C2H3 + CH4
#define R240 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   6.020000000e+01, \
      /*           n = */   1.560000000e+00, \
      /*        EovR = */   8.368543679e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H3, /* nu = */ 1 }, \
      { /* ind = */ iCH4, /* nu = */ 1 } \
                          } \
           }

// R 241: C2H4 + O2 <=> HO2 + C2H3
#define R241 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.100000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   3.019821444e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H4, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iC2H3, /* nu = */ 1 } \
                          } \
           }

// R 242: C2H5 + H (+ M) <=> C2H6 (+ M)
#define R242 { \
      /* ArrCoeffL = */   {  \
         /*           A = */   1.990000000e+29, \
         /*           n = */   -7.080000000e+00, \
         /*        EovR = */   3.364023722e+03, \
                          },  \
      /* ArrCoeffH = */   {  \
         /*           A = */   5.210000000e+11, \
         /*           n = */   -9.900000000e-01, \
         /*        EovR = */   7.950871324e+02, \
                          },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   1, \
   /*      Nthirdb = */   7, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ 0   , /* nu = */ 1 } \
                          }, \
   /*      thirdb  = */   { \
      { /* ind = */ iC2H6, /* eff = */ 3.0 }, \
      { /* ind = */ iCH2O, /* eff = */ 2.5 }, \
      { /* ind = */ iCH3OH, /* eff = */ 3.0 }, \
      { /* ind = */ iCH4, /* eff = */ 2.0 }, \
      { /* ind = */ iCO , /* eff = */ 1.5 }, \
      { /* ind = */ iCO2, /* eff = */ 2.0 }, \
      { /* ind = */ iH2O, /* eff = */ 6.0 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 }, \
      { /* ind = */ 0   , /* eff = */ 1 } \
                          }, \
/*      Ftype = */     F_Troe3, \
/*     FOData = */     { .Troe3 = { \
/*            alpha = */     8.420000000e-01, \
/*               T1 = */     2.219000000e+03, \
/*               T2 = */     6.882000000e+03, \
/*               T3 = */     1.250000000e+02  \
                       }} \
           }

// R 243: C2H5 + H <=> H2 + C2H4
#define R243 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.810000000e+06, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH2 , /* nu = */ 1 }, \
      { /* ind = */ iC2H4, /* nu = */ 1 } \
                          } \
           }

// R 244: C2H5 + O <=> CH3 + CH2O
#define R244 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   4.420000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          } \
           }

// R 245: C2H5 + O <=> H + CH3CHO
#define R245 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.890000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iH  , /* nu = */ 1 }, \
      { /* ind = */ iCH3CHO, /* nu = */ 1 } \
                          } \
           }

// R 246: C2H5 + O <=> OH + C2H4
#define R246 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   2.940000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iC2H4, /* nu = */ 1 } \
                          } \
           }

// R 247: C2H5 + O2 <=> HO2 + C2H4
#define R247 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.355000000e+01, \
      /*           n = */   1.090000000e+00, \
      /*        EovR = */   -9.938589155e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iHO2, /* nu = */ 1 }, \
      { /* ind = */ iC2H4, /* nu = */ 1 } \
                          } \
           }

// R 248: C2H5 + CH3 <=> CH4 + C2H4
#define R248 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.000000000e+05, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   0.000000000e+00, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH4, /* nu = */ 1 }, \
      { /* ind = */ iC2H4, /* nu = */ 1 } \
                          } \
           }

// R 249: C2H5 + CH2O <=> C2H6 + HCO
#define R249 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.500000000e-03, \
      /*           n = */   2.810000000e+00, \
      /*        EovR = */   2.948867466e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iCH2O, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iHCO, /* nu = */ 1 } \
                          } \
           }

// R 250: C2H5 + CH3OH <=> C2H6 + CH2OH
#define R250 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.200000000e-05, \
      /*           n = */   3.200000000e+00, \
      /*        EovR = */   3.610601377e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iCH3OH, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iCH2OH, /* nu = */ 1 } \
                          } \
           }

// R 251: C2H6 + H <=> C2H5 + H2
#define R251 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.133000000e+02, \
      /*           n = */   1.900000000e+00, \
      /*        EovR = */   3.789244372e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iH  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iH2 , /* nu = */ 1 } \
                          } \
           }

// R 252: C2H6 + O <=> OH + C2H5
#define R252 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.763000000e-01, \
      /*           n = */   2.800000000e+00, \
      /*        EovR = */   2.920183943e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iO  , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iOH , /* nu = */ 1 }, \
      { /* ind = */ iC2H5, /* nu = */ 1 } \
                          } \
           }

// R 253: C2H6 + OH <=> C2H5 + H2O
#define R253 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   9.463000000e+00, \
      /*           n = */   2.000000000e+00, \
      /*        EovR = */   5.002003858e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iOH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iH2O, /* nu = */ 1 } \
                          } \
           }

// R 254: C2H6 + CH <=> CH3 + C2H4
#define R254 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.077000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -1.318435625e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iCH , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iC2H4, /* nu = */ 1 } \
                          } \
           }

// R 255: C2H6 + CH2(S) <=> CH3 + C2H5
#define R255 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   3.300000000e+07, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   -3.321250047e+02, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iCH2_S, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iCH3, /* nu = */ 1 }, \
      { /* ind = */ iC2H5, /* nu = */ 1 } \
                          } \
           }

// R 256: C2H6 + CH3 <=> C2H5 + CH4
#define R256 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   5.600000000e+04, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   4.740329612e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iCH4, /* nu = */ 1 } \
                          } \
           }

// R 257: C2H6 + CH3 <=> C2H5 + CH4
#define R257 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   8.299000000e+08, \
      /*           n = */   0.000000000e+00, \
      /*        EovR = */   1.120167061e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iCH3, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iCH4, /* nu = */ 1 } \
                          } \
           }

// R 258: C2H6 + O2 <=> C2H5 + HO2
#define R258 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   7.290000000e-01, \
      /*           n = */   2.500000000e+00, \
      /*        EovR = */   2.473828065e+04, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iO2 , /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          } \
           }

// R 259: C2H6 + HO2 <=> C2H5 + H2O2
#define R259 { \
   /* ArrCoeff  = */   {  \
      /*           A = */   1.100000000e-01, \
      /*           n = */   2.500000000e+00, \
      /*        EovR = */   8.479252013e+03, \
                       },  \
   /* has_backward = */   true, \
   /*      Neducts = */   2, \
   /*      Npducts = */   2, \
   /*       educts = */   {  \
      { /* ind = */ iC2H6, /* nu = */ 1 }, \
      { /* ind = */ iHO2, /* nu = */ 1 } \
                          }, \
   /*       pducts = */   {  \
      { /* ind = */ iC2H5, /* nu = */ 1 }, \
      { /* ind = */ iH2O2, /* nu = */ 1 } \
                          } \
           }


//---------------------------------
// Initialization function
//---------------------------------

#ifndef __CUDACC__
inline Mix::Mix(const Config &config) :
species({H2, H, O, O2, OH, H2O, HO2, H2O2,
         CO, CO2, C, CH, CH2, CH2_S, CH3, CH4,
         HCO, CH2O, CH2OH, CH3O, CH3OH, C2H, C2H2, C2H3,
         C2H4, C2H5, C2H6, HCCO, CH2CO, CH2CHO, CH3CHO, CH3CO,
         H2CC }),
reactions({R1, R2, R3, R4, R5, R10, R12, R13,
         R14, R15, R16, R17, R18, R19, R21, R22,
         R23, R24, R25, R27, R28, R29, R30, R32,
         R33, R34, R35, R36, R37, R38, R39, R40,
         R41, R42, R44, R45, R46, R47, R48, R50,
         R52, R53, R54, R55, R56, R57, R58, R59,
         R60, R61, R62, R63, R64, R65, R66, R67,
         R68, R69, R70, R72, R73, R74, R75, R76,
         R77, R80, R81, R82, R83, R84, R85, R86,
         R87, R88, R89, R91, R92, R94, R95, R96,
         R97, R98, R99, R100, R101, R102, R103, R104,
         R106, R107, R108, R111, R112, R113, R114, R115,
         R116, R117, R118, R119, R122, R123, R124, R125,
         R126, R127, R128, R129, R130, R131, R132, R133,
         R134, R135, R136, R137, R138, R139, R140, R141,
         R142, R143, R144, R145, R146, R147, R148, R149,
         R150, R151, R152, R153, R154, R155, R156, R158,
         R159, R160, R161, R162, R163, R164, R165, R166,
         R167, R168, R171, R172, R173, R174, R175, R176,
         R177, R178, R180, R181, R182, R183, R184, R185,
         R186, R187, R188, R189, R191, R192, R193, R194,
         R195, R196, R197, R198, R199, R200, R203, R204,
         R205, R206, R207, R208, R209, R212, R213, R214,
         R215, R216, R217, R218, R219, R222, R223, R224,
         R225, R226, R227, R228, R229, R232, R233, R234,
         R235, R236, R237, R238, R239, R240, R241, R243,
         R244, R245, R246, R247, R248, R249, R250, R251,
         R252, R253, R254, R255, R256, R257, R258, R259
         }),
ThirdbodyReactions({R6, R7, R8, R9, R31 }),
FalloffReactions({R11, R20, R26, R43, R49, R51, R71, R78,
         R79, R90, R93, R105, R109, R110, R120, R121,
         R157, R169, R170, R179, R190, R201, R202, R210,
         R211, R220, R221, R230, R231, R242 })
{
// This executable is expecting FFCM-1Mix in the input file
assert(config.Flow.mixture.type == MixtureModel_FFCM1Mix);

// Store reference quantities
StoreReferenceQuantities(config.Flow.mixture.u.FFCM1Mix.PRef,
                         config.Flow.mixture.u.FFCM1Mix.TRef,
                         config.Flow.mixture.u.FFCM1Mix.LRef,
                         config.Flow.mixture.u.FFCM1Mix.XiRef);
};
#endif

//---------------------------------
// Cleanup
//---------------------------------

#undef iH2
#undef H2
#undef iH
#undef H
#undef iO
#undef O
#undef iO2
#undef O2
#undef iOH
#undef OH
#undef iH2O
#undef H2O
#undef iHO2
#undef HO2
#undef iH2O2
#undef H2O2
#undef iCO
#undef CO
#undef iCO2
#undef CO2
#undef iC
#undef C
#undef iCH
#undef CH
#undef iCH2
#undef CH2
#undef iCH2_S
#undef CH2_S
#undef iCH3
#undef CH3
#undef iCH4
#undef CH4
#undef iHCO
#undef HCO
#undef iCH2O
#undef CH2O
#undef iCH2OH
#undef CH2OH
#undef iCH3O
#undef CH3O
#undef iCH3OH
#undef CH3OH
#undef iC2H
#undef C2H
#undef iC2H2
#undef C2H2
#undef iC2H3
#undef C2H3
#undef iC2H4
#undef C2H4
#undef iC2H5
#undef C2H5
#undef iC2H6
#undef C2H6
#undef iHCCO
#undef HCCO
#undef iCH2CO
#undef CH2CO
#undef iCH2CHO
#undef CH2CHO
#undef iCH3CHO
#undef CH3CHO
#undef iCH3CO
#undef CH3CO
#undef iH2CC
#undef H2CC

#undef R1
#undef R2
#undef R3
#undef R4
#undef R5
#undef R6
#undef R7
#undef R8
#undef R9
#undef R10
#undef R11
#undef R12
#undef R13
#undef R14
#undef R15
#undef R16
#undef R17
#undef R18
#undef R19
#undef R20
#undef R21
#undef R22
#undef R23
#undef R24
#undef R25
#undef R26
#undef R27
#undef R28
#undef R29
#undef R30
#undef R31
#undef R32
#undef R33
#undef R34
#undef R35
#undef R36
#undef R37
#undef R38
#undef R39
#undef R40
#undef R41
#undef R42
#undef R43
#undef R44
#undef R45
#undef R46
#undef R47
#undef R48
#undef R49
#undef R50
#undef R51
#undef R52
#undef R53
#undef R54
#undef R55
#undef R56
#undef R57
#undef R58
#undef R59
#undef R60
#undef R61
#undef R62
#undef R63
#undef R64
#undef R65
#undef R66
#undef R67
#undef R68
#undef R69
#undef R70
#undef R71
#undef R72
#undef R73
#undef R74
#undef R75
#undef R76
#undef R77
#undef R78
#undef R79
#undef R80
#undef R81
#undef R82
#undef R83
#undef R84
#undef R85
#undef R86
#undef R87
#undef R88
#undef R89
#undef R90
#undef R91
#undef R92
#undef R93
#undef R94
#undef R95
#undef R96
#undef R97
#undef R98
#undef R99
#undef R100
#undef R101
#undef R102
#undef R103
#undef R104
#undef R105
#undef R106
#undef R107
#undef R108
#undef R109
#undef R110
#undef R111
#undef R112
#undef R113
#undef R114
#undef R115
#undef R116
#undef R117
#undef R118
#undef R119
#undef R120
#undef R121
#undef R122
#undef R123
#undef R124
#undef R125
#undef R126
#undef R127
#undef R128
#undef R129
#undef R130
#undef R131
#undef R132
#undef R133
#undef R134
#undef R135
#undef R136
#undef R137
#undef R138
#undef R139
#undef R140
#undef R141
#undef R142
#undef R143
#undef R144
#undef R145
#undef R146
#undef R147
#undef R148
#undef R149
#undef R150
#undef R151
#undef R152
#undef R153
#undef R154
#undef R155
#undef R156
#undef R157
#undef R158
#undef R159
#undef R160
#undef R161
#undef R162
#undef R163
#undef R164
#undef R165
#undef R166
#undef R167
#undef R168
#undef R169
#undef R170
#undef R171
#undef R172
#undef R173
#undef R174
#undef R175
#undef R176
#undef R177
#undef R178
#undef R179
#undef R180
#undef R181
#undef R182
#undef R183
#undef R184
#undef R185
#undef R186
#undef R187
#undef R188
#undef R189
#undef R190
#undef R191
#undef R192
#undef R193
#undef R194
#undef R195
#undef R196
#undef R197
#undef R198
#undef R199
#undef R200
#undef R201
#undef R202
#undef R203
#undef R204
#undef R205
#undef R206
#undef R207
#undef R208
#undef R209
#undef R210
#undef R211
#undef R212
#undef R213
#undef R214
#undef R215
#undef R216
#undef R217
#undef R218
#undef R219
#undef R220
#undef R221
#undef R222
#undef R223
#undef R224
#undef R225
#undef R226
#undef R227
#undef R228
#undef R229
#undef R230
#undef R231
#undef R232
#undef R233
#undef R234
#undef R235
#undef R236
#undef R237
#undef R238
#undef R239
#undef R240
#undef R241
#undef R242
#undef R243
#undef R244
#undef R245
#undef R246
#undef R247
#undef R248
#undef R249
#undef R250
#undef R251
#undef R252
#undef R253
#undef R254
#undef R255
#undef R256
#undef R257
#undef R258
#undef R259

#endif

#endif // __FFCM1MIX_HPP__
