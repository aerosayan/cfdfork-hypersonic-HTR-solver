import os
import sys
import unittest
import subprocess
sys.path.insert(1, os.path.expandvars("$HTR_DIR/solverTests/"))
import testAll

class unitTest(unittest.TestCase, testAll.Test3DTiledBase):
   testName = "3DPeriodic_TENOLAD"
   npart = 2
   def execute(self, name):
      return subprocess.check_output([testAll.executable, "-i", name+".json", "-o", name])

if __name__ == "__main__":
   unittest.main()
