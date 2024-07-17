import sys
from logger import *
import pathlib
import os
import subprocess
import json
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
loaders = ""
declarations = ""
for mat in os.listdir("./Project/materials"):
    matName = pathlib.Path(mat).stem
    Log("Creating material for "+mat)
    matContent = json.loads(open("./Project/materials/"+mat).read())
    Healthy("Loaded material "+mat)
    declarations = declarations+ "Material "+matName+";\n"
    Healthy("Declared material assets::materials::"+matName+";")
    loaders = loaders + "assets::materials::"+matName+".texture = assets::textures::"+matContent["texture"]+";\n"
    loaders = loaders + "assets::materials::"+matName+".shine = "+str(matContent["shine"])+";\n"
    loaders = loaders + "assets::materials::"+matName+".smooth = "+str(matContent["smooth"]).lower()+";\n"
    loaders = loaders + "assets::materials::"+matName+".filter = "+str(matContent["filter"]).lower()+";\n"
    loaders = loaders + "assets::materials::"+matName+".lit = "+str(matContent["lit"]).lower()+";\n"
    loaders = loaders + "assets::materials::"+matName+".shadows = "+str(matContent["shadows"]).lower()+";\n"
    loaders = loaders + "assets::materials::"+matName+".cast = "+str(matContent["cast"]).lower()+";\n"
    loaders = loaders + "assets::materials::"+matName+".celshaded = "+str(matContent["celshaded"]).lower()+";\n"
    loaders = loaders + "assets::materials::"+matName+".mipmaps = "+str(matContent["mipmaps"]).lower()+";\n"
    Healthy("Created loader for texture assets::materials::"+matName+";")
Log("Adding materials to source")
try:
    cake2kFile = open("./Build/Main.cpp","r")
    srcMain = cake2kFile.read()
    cake2kFile.close()
    cake2kFile = open("./Build/Main.cpp","w")
    srcMain = re.sub("using namespace cake2k::assetGen::loadAssets::materials::defines\;",declarations,srcMain)
    Healthy("Added material declarations to source")
    srcMain = re.sub("cake2k::assetGen::loadAssets::materials::load\(\)\;",loaders,srcMain)
    Healthy("Added material loading to source")  
    cake2kFile.write(srcMain)
    cake2kFile.close()
except Exception as e:
    Error("Could not add textures to source - "+str(e))
    exit(1)