#ifdef CAKE2K_TARGET_PSP
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
PSP_MODULE_INFO(CAKE2K_APPNAME, 0, 1, 1);
#define print pspDebugScreenPrintf
#endif
#include "Dummy.hpp"
#include "Textures.hpp"
namespace assets{
    namespace textures{
        using namespace cake2k::assetGen::loadAssets::textures::defines;
    }
    using namespace cake2k::assetGen::loadAssets::materials::defines;
}
using namespace cake2k::sourceGen::replaceScripts::namespaces;
int main(void){
#ifdef CAKE2K_TARGET_PSP
    pspDebugScreenInit();
    print("Cake2k init.");
#endif
    cake2k::assetGen::loadAssets::textures::load();
    cake2k::assetGen::loadAssets::materials::load();
    cake2k::sourceGen::replaceScripts::starts();
    while(1){
        cake2k::sourceGen::replaceScripts::frames();
    }
}