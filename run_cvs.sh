#Galaxy simulation
GALAXYFILE=full_galaxy_plus_CVs.dat
 
#Observation time
T=125829120 #4 year
 
#Calculate LISA orbits
/hildafs/projects/phy230054p/wballard/ldasoft-old-commit/gbfisher/src/OrbitFile
 
#Simulate LISA response to galaxy
/hildafs/projects/phy230054p/wballard/ldasoft-old-commit/gbfisher/src/Galaxy $GALAXYFILE EccentricInclined.txt $T
 
#Get initial estiamte of confusion noise level
/hildafs/projects/phy230054p/wballard/ldasoft-old-commit/gbfisher/src/Confusion_Fit Galaxy_XAE.dat EccentricInclined.txt
 
#Find and regress resolvable binaries
/hildafs/projects/phy230054p/wballard/ldasoft-old-commit/gbfisher/src/Bright_Remove Galaxy_XAE.dat Confusion_XAE_0.dat Bright.dat EccentricInclined.txt
 
