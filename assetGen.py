import sys

import pywavefront.obj
from logger import *
import pathlib
import os
import subprocess
import shutil
import json
import re
try:
    import pywavefront
    Healthy("Python module pywavefront loaded")
except:
    Error("Python module pyWavefront not installed")
    exit(1)
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
indices = ""
for object in os.listdir("./Project/models/"):
    if(re.findall("\.obj",object)):
        headerName = re.sub("\.","_",object)
        modelOut = open("./Build/"+srcPth+"/"+headerName+".h","w")
        objSrc = pywavefront.Wavefront("./Project/models/"+object,collect_faces=True)
        hdrCnt = 0
        indices = "namespace assets{\nnamespace models\n{"
        for mesh in objSrc.mesh_list:
            print("new mesh")
            print(mesh.materials[0].texture.path)
            indices = indices+"void drawMesh"+headerName+str(hdrCnt)+"(){\n"
            hdrCnt+=1
            indices += "GX_Begin(GX_TRIANGLES,GX_VTXFMT0,"+str(len(mesh.faces)*3)+");\n"
            for face in mesh.faces:
                indices += "GX_Position3f32("+str(objSrc.vertices[face[0]][0])+"f,"+str(objSrc.vertices[face[0]][1])+"f,"+str(objSrc.vertices[face[0]][2])+"f);\n"    
                indices += "GX_Color1u32(0xFFFFFFFF);\n"
                indices += "GX_Position3f32("+str(objSrc.vertices[face[1]][0])+"f,"+str(objSrc.vertices[face[1]][1])+"f,"+str(objSrc.vertices[face[1]][2])+"f);\n"
                indices += "GX_Color1u32(0xFFFFFFFF);\n"
                indices += "GX_Position3f32("+str(objSrc.vertices[face[2]][0])+"f,"+str(objSrc.vertices[face[2]][1])+"f,"+str(objSrc.vertices[face[2]][2])+"f);\n"
                indices += "GX_Color1u32(0xFFFFFFFF);\n"
                #no UVS yet :)
                #indices += "GX_Position2f32("+str(objSrc.UVS[face[0]][0])+"f,"+str(objSrc.vertices[face[0]][1])+"f);\n"
            indices += "GX_End();\n}\n"
        indices += "}\n}"
        modelOut.write(indices)
        modelOut.close()
        includes += "#include \""+headerName+".h\"\n"


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