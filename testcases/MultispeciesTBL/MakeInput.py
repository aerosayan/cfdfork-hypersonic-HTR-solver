#!/usr/bin/env python3

import argparse
import sys
import os
import json
import numpy as np
import h5py
from random import *
from scipy.integrate import odeint
from scipy.optimize import fsolve
from joblib import Parallel, delayed
import pandas

# load local modules
sys.path.insert(0, os.path.expandvars("$HTR_DIR/scripts/modules"))
import gridGen

parser = argparse.ArgumentParser()
parser.add_argument('--np', nargs='?', default=1, type=int,
                    help='number of cores')
parser.add_argument('base_json', type=argparse.FileType('r'), default='base.json')
args = parser.parse_args()

##############################################################################
#                          Read similarity solution                          #
##############################################################################

CBL = pandas.read_csv("SimilaritySolution.dat")
etaB = CBL["eta"][:].values
fB = CBL["f"][:].values
uB = CBL["u"][:].values
TB = CBL["T"][:].values
N2B = CBL["X_N2"][:].values
O2B = CBL["X_O2"][:].values
NOB = CBL["X_NO"][:].values
NB  = CBL["X_N" ][:].values
OB  = CBL["X_O" ][:].values
muB = CBL["mu"][:].values
rhoB = CBL["rho"][:].values
cB = CBL["SoS"][:].values
Rex0 = CBL["Rex"][0]

x0 = Rex0*muB[-1]/(uB[-1]*rhoB[-1])
deltaStarIn = 0.0
for i in range(uB.size-1):
   deltaStarIn += 0.5*((1.0 - uB[i+1]*rhoB[i+1]/(uB[-1]*rhoB[-1]))*rhoB[-1]/rhoB[i+1] +
                       (1.0 - uB[i  ]*rhoB[i  ]/(uB[-1]*rhoB[-1]))*rhoB[-1]/rhoB[i  ] )*(etaB[i+1] - etaB[i])
deltaStarIn *= x0*np.sqrt(2.0/Rex0)
print("Re_delta0 = ", uB[-1]*rhoB[-1]*deltaStarIn/muB[-1])

yB = np.zeros(etaB.size)
for i in range(etaB.size):
   if (i != 0) :
      rhoMid = 0.5*(rhoB[i  ] + rhoB[i-1])
      dyB = x0*np.sqrt(2/Rex0)*rhoB[-1]/rhoMid*(etaB[i] - etaB[i-1])
      yB[i] = yB[i-1] + dyB

vB = 0.5*yB/x0*uB - rhoB[-1]/rhoB*1.0/np.sqrt(2*Rex0)*fB

##############################################################################
#                                 Setup Case                                 #
##############################################################################

# Read base config
config = json.load(args.base_json)

ReIn   = config["Case"]["ReInlet"]
MaInf  = config["Case"]["MaInf"]
TInf   = config["Case"]["TInf"]
PInf   = config["Case"]["PInf"]
TwOvT  = config["Case"]["TwOvTInf"]
xTurb  = config["Case"]["xTurb"]
yPlus  = config["Case"]["yPlus"]
FTT    = config["Case"]["FlowThroughTimesNoStat"]
FTTS   = config["Case"]["FlowThroughTimesStat"]

# Read properties
Pr     = 0.71
gamma  = 1.4
R      = 287.15

# Simulation setup
assert config["Flow"]["turbForcing"]["type"] == "OFF"
assert config["Flow"]["initCase"]["type"] == "Restart"
restartDir = "InitialCase"
config["Flow"]["initCase"]["restartDir"] = restartDir

# Free-stream mixture properties
cInf  =  cB[-1]
muInf = muB[-1]


# Free-stream conditions
assert abs(TB[-1] - TInf) < 1e-3
UInf   =   uB[-1]
rhoInf = rhoB[-1]
TInf   = TB[-1]
assert abs(UInf/cInf - MaInf)  < 1e-3

# Inlet displacement thickness
assert abs(deltaStarIn -muInf*ReIn/(UInf*rhoInf)) < 1e-3

# Wall properties
Tw   =   TB[0]
muW  =  muB[0]
rhoW = rhoB[0]
assert abs(Tw/TB[-1] - TwOvT) < 1e-3

##############################################################################
#                        Compute similarity solution                         #
##############################################################################

# Reference friction coefficient
def getCfTurb(xGrid):

   def VanDriestII(Cf):
      Rexv = (xGrid-xTurb)*ReIn

      r = Pr**(1.0/3.0)
      Taw = TInf*(1.0 + r*0.5*(gamma - 1.0)*MaInf**2)

      a = np.sqrt(r*0.5*(gamma - 1.0)*MaInf**2*TInf/Tw)
      b = (Taw/Tw - 1.0)

      A = (2*a**2 - b)/np.sqrt(b**2 + 4*a**2)
      B =           b /np.sqrt(b**2 + 4*a**2)

      res = (np.arcsin(A) + np.arcsin(B))/np.sqrt(Cf*(Taw/TInf - 1.0))
      res-= 4.15*np.log10(Rexv*Cf*muInf/muW)
      res-= 1.7
      return res

   cf = fsolve(VanDriestII, 1e-4, xtol=1e-10)

   return cf

Cf = getCfTurb(config["Grid"]["xWidth"]+x0/deltaStarIn)
TauW = Cf*(rhoInf*UInf**2)*0.5
uTau = np.sqrt(TauW/rhoW)
deltaNu = muW/(uTau*rhoW)
tNu = deltaNu**2*rhoW/muW

# Get VorticityScale
delta = 0.0
for i in range(len(uB)):
   if (uB[i] > 0.99*UInf):
      delta = yB[i]
      break

# Normalization scales
LRef = config["Flow"]["mixture"]["LRef"] = deltaStarIn
TRef = config["Flow"]["mixture"]["TRef"] = TInf
PRef = config["Flow"]["mixture"]["PRef"] = PInf
rhoRef = rhoInf
uRef = np.sqrt(PRef/rhoRef)
config["Flow"]["mixture"]["XiRef"] = [
   {"Name" : "N2", "MolarFrac" : N2B[-1]},
   {"Name" : "O2", "MolarFrac" : O2B[-1]},
   {"Name" : "NO", "MolarFrac" : NOB[-1]},
   {"Name" :  "O", "MolarFrac" :  OB[-1]},
   {"Name" :  "N", "MolarFrac" :  NB[-1]}]

# Normalize everything
TInf = 1.0
PInf = 1.0
rhoInf = 1.0
UInf /= uRef
cInf /= uRef
muInf /= np.sqrt(config["Flow"]["mixture"]["PRef"]*rhoRef)*LRef

Tw /= config["Flow"]["mixture"]["TRef"]
muW /= np.sqrt(config["Flow"]["mixture"]["PRef"]*rhoRef)*LRef
rhoW /= rhoRef
delta /= config["Flow"]["mixture"]["LRef"]

config["Integrator"]["EulerScheme"]["vorticityScale"] = UInf/delta

x0 /= LRef
deltaStarIn /= LRef
deltaNu /= LRef
config["Grid"]["origin"][0] = x0

uB /= uRef
TB /= TRef
rhoB /= rhoRef

##############################################################################
#                            Boundary conditions                             #
##############################################################################
assert config["BC"]["xBCLeft"]["type"] == "NSCBC_Inflow"
assert config["BC"]["xBCLeft"]["VelocityProfile"]["type"] == "File"
config["BC"]["xBCLeft"]["VelocityProfile"]["FileDir"] = restartDir
assert config["BC"]["xBCLeft"]["TemperatureProfile"]["type"] == "File"
config["BC"]["xBCLeft"]["TemperatureProfile"]["FileDir"] = restartDir
assert config["BC"]["xBCLeft"]["MixtureProfile"]["type"] == "File"
config["BC"]["xBCLeft"]["MixtureProfile"]["FileDir"] = restartDir
config["BC"]["xBCLeft"]["P"] = PInf

assert config["BC"]["xBCRight"]["type"] == "NSCBC_Outflow"
config["BC"]["xBCRight"]["P"] = PInf

assert config["BC"]["yBCLeft"]["type"] == "SuctionAndBlowingWall"
assert config["BC"]["yBCLeft"]["TemperatureProfile"]["type"] == "Constant"
config['BC']["yBCLeft"]["TemperatureProfile"]["temperature"] = Tw
config["BC"]["yBCLeft"]["Xmin"]  = 15*deltaStarIn + x0
config["BC"]["yBCLeft"]["Xmax"]  = 20*deltaStarIn + x0
config["BC"]["yBCLeft"]["X0"]    = 0.5*(config["BC"]["yBCLeft"]["Xmin"] + config["BC"]["yBCLeft"]["Xmax"])
config["BC"]["yBCLeft"]["sigma"] = 0.3*(config["BC"]["yBCLeft"]["X0"] - config["BC"]["yBCLeft"]["Xmin"])
config["BC"]["yBCLeft"]["Zw"]    = 0.1*config["Grid"]["zWidth"]

config["BC"]["yBCLeft"]["A"]     = [ 0.05*UInf, 0.05*UInf]
config["BC"]["yBCLeft"]["omega"] = [ 0.9*cInf/deltaStarIn, 0.9*cInf/deltaStarIn]
config["BC"]["yBCLeft"]["beta"]  = [ 0.3/deltaStarIn, -0.3/deltaStarIn]

assert config["BC"]["yBCRight"]["type"] == "NSCBC_Outflow"
config["BC"]["yBCRight"]["P"] = PInf

##############################################################################
#                              Generate Grid                                 #
##############################################################################

def objective(yStretching):
   yGrid, dy = gridGen.GetGrid(config["Grid"]["origin"][1],
                               config["Grid"]["yWidth"],
                               config["Grid"]["yNum"], 
                               config["Grid"]["yType"],
                               yStretching,
                               False,
                               StagMinus=True)
   return dy[1]/deltaNu - yPlus

config["Grid"]["yStretching"], = fsolve(objective, 1.0)

xGrid, dx = gridGen.GetGrid(config["Grid"]["origin"][0],
                            config["Grid"]["xWidth"],
                            config["Grid"]["xNum"], 
                            config["Grid"]["xType"],
                            1.0,
                            False)

yGrid, dy = gridGen.GetGrid(config["Grid"]["origin"][1],
                            config["Grid"]["yWidth"],
                            config["Grid"]["yNum"], 
                            config["Grid"]["yType"],
                            config["Grid"]["yStretching"],
                            False,
                            StagMinus=True,
                            dx=yPlus*deltaNu)

zGrid, dz = gridGen.GetGrid(config["Grid"]["origin"][2],
                            config["Grid"]["zWidth"],
                            config["Grid"]["zNum"], 
                            config["Grid"]["zType"],
                            1.0,
                            True)

print("        L_x        x          L_y        x          L_z")

print(config["Grid"]["xWidth"]/deltaNu, " x ",
      config["Grid"]["yWidth"]/deltaNu, " x ",
      config["Grid"]["zWidth"]/deltaNu)

print(dx[0]/deltaNu, " x ",
      dy[1]/deltaNu, " x ",
      dz[0]/deltaNu)

# Set maxTime
config["Integrator"]["maxTime"] = config["Grid"]["xWidth"]/UInf*FTT

with open("NoStats.json", 'w') as fout:
   json.dump(config, fout, indent=3)

config["Integrator"]["maxTime"] = config["Grid"]["xWidth"]/UInf*FTT + FTTS*2*np.pi/config["BC"]["yBCLeft"]["omega"][0]

# Setup averages
config["IO"]["YZAverages"] = [{"fromCell" : [0, 0, 0],          "uptoCell" : [config["Grid"]["xNum"]+1, 0, config["Grid"]["zNum"]]}]

with open("Stats.json", 'w') as fout:
   json.dump(config, fout, indent=3)

# Load mapping
assert config["Mapping"]["tiles"][0] % config["Mapping"]["tilesPerRank"][0] == 0
assert config["Mapping"]["tiles"][1] % config["Mapping"]["tilesPerRank"][1] == 0
assert config["Mapping"]["tiles"][2] % config["Mapping"]["tilesPerRank"][2] == 0
Ntiles = config["Mapping"]["tiles"]
Ntiles[0] = int(Ntiles[0]/config["Mapping"]["tilesPerRank"][0])
Ntiles[1] = int(Ntiles[1]/config["Mapping"]["tilesPerRank"][1])
Ntiles[2] = int(Ntiles[2]/config["Mapping"]["tilesPerRank"][2])

assert config["Grid"]["xNum"] % Ntiles[0] == 0
assert config["Grid"]["yNum"] % Ntiles[1] == 0
assert config["Grid"]["zNum"] % Ntiles[2] == 0

NxTile = int(config["Grid"]["xNum"]/Ntiles[0])
NyTile = int(config["Grid"]["yNum"]/Ntiles[1])
NzTile = int(config["Grid"]["zNum"]/Ntiles[2])

halo = [1, 1, 0]

##############################################################################
#                     Produce restart and profile files                      #
##############################################################################
if not os.path.exists(restartDir):
   os.makedirs(restartDir)

def writeTile(xt, yt, zt):
   lo_bound = [(xt  )*NxTile  +halo[0], (yt  )*NyTile  +halo[1], (zt  )*NzTile  +halo[2]]
   hi_bound = [(xt+1)*NxTile-1+halo[0], (yt+1)*NyTile-1+halo[1], (zt+1)*NzTile-1+halo[2]]
   if (xt == 0): lo_bound[0] -= halo[0]
   if (yt == 0): lo_bound[1] -= halo[1]
   if (zt == 0): lo_bound[2] -= halo[2]
   if (xt == Ntiles[0]-1): hi_bound[0] += halo[0]
   if (yt == Ntiles[1]-1): hi_bound[1] += halo[1]
   if (zt == Ntiles[2]-1): hi_bound[2] += halo[2]
   filename = ('%s,%s,%s-%s,%s,%s.hdf'
      % (lo_bound[0],  lo_bound[1],  lo_bound[2],
         hi_bound[0],  hi_bound[1],  hi_bound[2]))
   print("Working on: ", filename)

   shape = [hi_bound[2] - lo_bound[2] +1,
            hi_bound[1] - lo_bound[1] +1,
            hi_bound[0] - lo_bound[0] +1]

   centerCoordinates = np.ndarray(shape, dtype=np.dtype('(3,)f8'))
   cellWidth         = np.ndarray(shape, dtype=np.dtype('(3,)f8'))
   rho               = np.ndarray(shape)
   pressure          = np.ndarray(shape)
   temperature       = np.ndarray(shape)
   MolarFracs        = np.ndarray(shape, dtype=np.dtype('(5,)f8'))
   velocity          = np.ndarray(shape, dtype=np.dtype('(3,)f8'))
   dudtBoundary      = np.ndarray(shape, dtype=np.dtype('(3,)f8'))
   dTdtBoundary      = np.ndarray(shape)
   pressure[:] = PInf
   dudtBoundary[:] = [0.0, 0.0, 0.0]
   dTdtBoundary[:] = 0.0
   for (k,kc) in enumerate(centerCoordinates):
      for (j,jc) in enumerate(kc):
         for (i,ic) in enumerate(jc):
            Re = rhoInf*UInf*xGrid[i+lo_bound[0]]/muInf
            yB1 = yB*np.sqrt(Re/Rex0)
            vB1 = vB*np.sqrt(Rex0/Re)

            u  = np.interp(yGrid[j+lo_bound[1]], yB1, uB)
            v  = np.interp(yGrid[j+lo_bound[1]], yB1, vB1)
            T  = np.interp(yGrid[j+lo_bound[1]], yB1, TB)
            N2 = np.interp(yGrid[j+lo_bound[1]], yB1, N2B)
            O2 = np.interp(yGrid[j+lo_bound[1]], yB1, O2B)
            NO = np.interp(yGrid[j+lo_bound[1]], yB1, NOB)
            N  = np.interp(yGrid[j+lo_bound[1]], yB1, NB)
            O  = np.interp(yGrid[j+lo_bound[1]], yB1, OB)
            rh = np.interp(yGrid[j+lo_bound[1]], yB1, rhoB)

            centerCoordinates[k,j,i] = [xGrid[i+lo_bound[0]], yGrid[j+lo_bound[1]], zGrid[k+lo_bound[2]]]
            cellWidth        [k,j,i] = [   dx[i+lo_bound[0]],    dy[j+lo_bound[1]],    dz[k+lo_bound[2]]]
            temperature      [k,j,i] = T
            rho              [k,j,i] = rh
            MolarFracs       [k,j,i] = [N2, O2, NO, N, O]
            velocity         [k,j,i] = [u, v, 0.0]

   with h5py.File(os.path.join(restartDir, filename), 'w') as fout:
      fout.attrs.create("SpeciesNames", ["N2".encode(),
                                         "O2".encode(),
                                         "NO".encode(),
                                          "N".encode(),
                                          "O".encode()], dtype="S20")
      fout.attrs.create("timeStep", 0)
      fout.attrs.create("simTime", 0.0)
      fout.attrs.create("channelForcing", 0.0)

      fout.create_dataset("centerCoordinates",     shape=shape, dtype = np.dtype("(3,)f8"))
      fout.create_dataset("cellWidth",             shape=shape, dtype = np.dtype("(3,)f8"))
      fout.create_dataset("rho",                   shape=shape, dtype = np.dtype("f8"))
      fout.create_dataset("pressure",              shape=shape, dtype = np.dtype("f8"))
      fout.create_dataset("temperature",           shape=shape, dtype = np.dtype("f8"))
      fout.create_dataset("MolarFracs",            shape=shape, dtype = np.dtype("(5,)f8"))
      fout.create_dataset("velocity",              shape=shape, dtype = np.dtype("(3,)f8"))
      fout.create_dataset("dudtBoundary",          shape=shape, dtype = np.dtype("(3,)f8"))
      fout.create_dataset("dTdtBoundary",          shape=shape, dtype = np.dtype("f8"))
      fout.create_dataset("MolarFracs_profile",    shape=shape, dtype = np.dtype("(5,)f8"))
      fout.create_dataset("velocity_profile",      shape=shape, dtype = np.dtype("(3,)f8"))
      fout.create_dataset("temperature_profile",   shape=shape, dtype = np.dtype("f8"))

      fout["centerCoordinates"][:] = centerCoordinates
      fout["cellWidth"][:] = cellWidth
      fout["rho"][:] = rho
      fout["pressure"][:] = pressure
      fout["temperature"][:] = temperature
      fout["MolarFracs"][:] = MolarFracs
      fout["velocity"][:] = velocity
      fout["dudtBoundary"][:] = dudtBoundary
      fout["dTdtBoundary"][:] = dTdtBoundary
      fout["MolarFracs_profile"][:] = MolarFracs
      fout["velocity_profile"][:] = velocity
      fout["temperature_profile"][:] = temperature

Parallel(n_jobs=args.np)(delayed(writeTile)(x, y, z) for x, y, z in np.ndindex((Ntiles[0], Ntiles[1], Ntiles[2])))

