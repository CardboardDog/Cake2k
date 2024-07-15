import sys
from logger import *
import pathlib
import os
import subprocess
import re
Log("Generating assets using - "+sys.argv[1])
declarations = ""
loaders = ""
if(sys.argv[1] == "psp"):
    for image in os.listdir("./Project/textures"):
        Log("Converting texture "+image)
        try:
            subprocess.run(["./SDKS/image/magick","./Project/textures/"+image,"-depth","16","./Build/"+pathlib.Path(image).stem+".png"],check=True)
            Healthy("Converted image to 16 bit ARGB")
        except Exception as e:
            Error("Can not convert "+image+" to 16 bit PNG - "+str(e))
            exit(1)
        imageName = pathlib.Path(image).stem
        Log("Creating texture for "+image)
        declarations = declarations+ "Texture* "+imageName+";\n"
        Healthy("Declared texture assets::textures::"+imageName+";")
        loaders = loaders + "assets::textures::"+imageName+" = loadTexture(\""+imageName+".png\",GU_TRUE);\n"
        Healthy("Created loader for texture assets::textures::"+imageName+";")
    Log("Adding textures to source")
    try:
        cake2kFile = open("./Build/Main.cpp","r")
        srcMain = cake2kFile.read()
        cake2kFile.close()
        cake2kFile = open("./Build/Main.cpp","w")
        srcMain = re.sub("using namespace cake2k::assetGen::loadAssets::textures::defines\;",declarations,srcMain)
        Healthy("Added texture declarations to source")
        srcMain = re.sub("cake2k::assetGen::loadAssets::textures::load\(\)\;",loaders,srcMain)
        Healthy("Added texture loading to source")
        cake2kFile.write(srcMain)
        cake2kFile.close()
    except Exception as e:
        Error("Could not add textures to source - "+str(e))
        exit(1)
    Healthy("Added textures to source")