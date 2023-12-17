#Galaxy simulation
GALAXYFILE=full_galaxy.dat
 
#Observation time
T=125829120 #4 year
 
#Calculate LISA orbits
/hildafs/projects/phy230054p/wballard/ldasoft-old-commit/bin/OrbitFile
 
#Simulate LISA response to galaxy
/hildafs/projects/phy230054p/wballard/ldasoft-old-commit/bin/Galaxy $GALAXYFILE EccentricInclined.txt $T
 
#Get initial estiamte of confusion noise level
/hildafs/projects/phy230054p/wballard/ldasoft-old-commit/bin/Confusion_Fit Galaxy_XAE.dat EccentricInclined.txt
 
#Find and regress resolvable binaries
/hildafs/projects/phy230054p/wballard/ldasoft-old-commit/bin/Bright_Remove Galaxy_XAE.dat Confusion_XAE_0.dat Bright.dat EccentricInclined.txt
 
