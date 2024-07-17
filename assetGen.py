import sys
from logger import *
import pathlib
import os
import subprocess
import shutil
import json
import re
Log("Generating assets using - "+sys.argv[1])
declarations = ""
loaders = ""
matDeclarations = ""
matLoaders = ""
cPth = ""
srcPth = ""
includes = ""
if(sys.argv[1] == "wii"):
    cPth = "/data/"
    srcPth = "/source/"

for image in os.listdir("./Project/textures"):
    shutil.copy2("./Project/textures/"+image,"./Build/"+cPth)
    name = pathlib.Path(image).stem
    declarations += "GRRLIB_texImg* "+name+";"
    loaders += "assets::textures::"+name+" = GRRLIB_LoadTexture("+re.sub("\.","_",image)+");"
    includes += "#include \""+re.sub("\.","_",image)+".h\"\n"

for material in os.listdir("./Project/materials"):
    mat = json.loads(open("./Project/materials/"+material,"r").read())
    name = pathlib.Path(material).stem
    matDeclarations += "Material "+name+";"
    matLoaders += "assets::materials::"+name+".texture = assets::textures::"+str(mat["texture"])+";"
    matLoaders += "assets::materials::"+name+".shine = "+str(mat["shine"])+";"
    matLoaders += "assets::materials::"+name+".smooth = "+str(mat["smooth"]).lower()+";"
    matLoaders += "assets::materials::"+name+".filter = "+str(mat["filter"]).lower()+";"
    matLoaders += "assets::materials::"+name+".lit = "+str(mat["lit"]).lower()+";"
    matLoaders += "assets::materials::"+name+".shadows = "+str(mat["shadows"]).lower()+";"
    matLoaders += "assets::materials::"+name+".cast = "+str(mat["cast"]).lower()+";"
    matLoaders += "assets::materials::"+name+".celshaded = "+str(mat["celshaded"]).lower()+";"
    matLoaders += "assets::materials::"+name+".mipmaps = "+str(mat["mipmaps"]).lower()+";"
srcFl = open("./Build/"+srcPth+"/Main.cpp","r")
srcMain = srcFl.read()
srcFl.close()

srcMain = re.sub("using namespace cake2k::assetGen::loadAssets::textures::defines\;",declarations,srcMain)
srcMain = re.sub("cake2k::assetGen::loadAssets::textures::load\(\)\;",loaders,srcMain)
srcMain = re.sub("using namespace cake2k::assetGen::loadAssets::materials::defines\;",matDeclarations,srcMain)
srcMain = re.sub("cake2k::assetGen::loadAssets::materials::load\(\)\;",matLoaders,srcMain)
srcMain = re.sub("#include \"Dummy.hpp\"",includes,srcMain)

srcFl = open("./Build/"+srcPth+"/Main.cpp","w")
srcFl.write(srcMain)
srcFl.close()