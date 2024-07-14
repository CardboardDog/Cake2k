#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include "Dummy.hpp"
PSP_MODULE_INFO("Cake2k", 0, 1, 1);
#define print pspDebugScreenPrintf
using namespace cake2d::sourceGen::replaceScripts::namespaces;
int main(void){
    pspDebugScreenInit();
    print("Cake2k init.");
    cake2d::sourceGen::replaceScripts::starts();
    while(1){
        cake2d::sourceGen::replaceScripts::frames();
    }
}