#include "Dummy.hpp"
#include "Materials.hpp"
#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
namespace assets{
    namespace textures{
        //using namespace cake2k::assetGen::loadAssets::textures::defines;
    }
    namespace materials{
        //using namespace cake2k::assetGen::loadAssets::materials::defines;
    }
}
using namespace cake2k::sourceGen::replaceScripts::namespaces;
int main(void){
	GRRLIB_Init();
	WPAD_Init();
    //cake2k::assetGen::loadAssets::textures::load();
    //cake2k::assetGen::loadAssets::materials::load();
	cake2k::sourceGen::replaceScripts::starts();
    while(1){
		WPAD_ScanPads();
		GRRLIB_SetBackgroundColour(255,85,10,0xFF);
		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;
        cake2k::sourceGen::replaceScripts::frames();
		GRRLIB_Render();
    }
	GRRLIB_Exit();
	exit(0);
}