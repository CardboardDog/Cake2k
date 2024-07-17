from logger import *
import shutil
import pathlib
import re
import os
import json
import sys
srcPth = ""
if sys.argv[1] == "wii":
    scrPath = "/source/"
try:
    import pywavefront
    Healthy("Python module pywavefront loaded")
except:
    Error("Python module pyWavefront not installed")
    exit(1)
Log("Copying Cake2k source")
try:
    for source in os.listdir("./Cake2k"):
        shutil.copy2("./Cake2k/"+source,"./Build"+scrPath+"/")
        Healthy("Copied Cake2k source file "+source)
except Exception as e:
    Error("Could not copy Cake2k source - " +str(e))
    exit(1)
Healthy("Source copied")
namespaces = ""
startCalls = ""
frameCalls = ""
for script in os.listdir("./Project/scripts"):
    if(os.path.isfile("./Project/scripts/"+script)):
        Log("Adding script "+script)
        try:
            scriptFile = open("./Project/scripts/"+script,"r")
            content = scriptFile.read()
            namespaces = namespaces+content+"\n"
            namespace = pathlib.Path(script).stem
            Healthy("Loaded namespaces from "+script)
            startCalls = startCalls+"\t"+namespace+"::start();\n"
            Healthy("Loaded start from "+namespace+"::start();")
            frameCalls = frameCalls+"\t\t"+namespace+"::frame();\n"
            Healthy("Loaded frame from "+namespace+"::frame();")
            scriptFile.close()
        except Exception as e:
            Warn("Could not add script "+script+" - "+str(e))
Log("Implementing scripts")
try:
    cake2kFile = open("./Build"+scrPath+"/Main.cpp","r")
    srcMain = cake2kFile.read()
    cake2kFile.close()
    cake2kFile = open("./Build"+scrPath+"/Main.cpp","w")
    srcMain = re.sub("using namespace cake2k::sourceGen::replaceScripts::namespaces;",namespaces,srcMain)
    Healthy("Implemented namespaces")
    srcMain = re.sub("cake2k::sourceGen::replaceScripts::starts\(\)\;",startCalls,srcMain)
    Healthy("Implemented start")
    srcMain = re.sub("cake2k::sourceGen::replaceScripts::frames\(\)\;",frameCalls,srcMain)
    Healthy("Implemented frame")
    Log("Assuming sourceGen is replaced")
    Log("Removing dummy header")
    Healthy("Dummy header removed")
except Exception as e:
    Error("Could not implement scripts - "+str(e))
    exit(1)
Log("Adding export settings")
try:
    settings = json.loads(open("./Project/app.2ki","r").read())
    Healthy("Loaded export settings")
    srcMain = "#define CAKE2K_APPNAME \""+settings["Name"]+"\"\n"+srcMain
    Healthy("Added CAKE2K_APPNAME to source")
    makefile = open("./Build/Makefile","r")
    makefileSrc = makefile.read()
    makefile.close()
    makefile = open("./Build/Makefile","w")
    makefileSrc = "CAKE2K_APPNAME := "+settings["Name"]+"\n"+makefileSrc
    makefile.write(makefileSrc)
    makefile.close()
    Healthy("Added CAKE2K_APPNAME to make")
    cake2kFile.write(srcMain)
    cake2kFile.close()
except Exception as e:
    Error("Could not add export settings  - "+str(e))
    exit(1)
Healthy("Scripts implemented")