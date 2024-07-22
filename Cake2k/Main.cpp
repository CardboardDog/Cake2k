#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "Materials.hpp"
#include "Dummy.hpp"
namespace assets{
    namespace textures{
        using namespace cake2k::assetGen::loadAssets::textures::defines;
    }
    namespace materials{
        using namespace cake2k::assetGen::loadAssets::materials::defines;
    }
}
using namespace cake2k::sourceGen::replaceScripts::namespaces;
int main(void){
    float rotate = 0;
	GRRLIB_Init();
	WPAD_Init();
    cake2k::assetGen::loadAssets::textures::load();
    cake2k::assetGen::loadAssets::materials::load();
	cake2k::sourceGen::replaceScripts::starts();
    while(1){
		WPAD_ScanPads();
		GRRLIB_SetBackgroundColour(255,85,10,0xFF);
		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;
        GRRLIB_3dMode(0.1,1000,45,1,0);// borrowed from GRRLIB examples :)
        GRRLIB_ObjectView(0,0,-30,rotate,rotate*2,rotate*3,1,1,1);
        useMaterial(&assets::materials::example);
        assets::models::drawMeshcubeThing_obj0();
        cake2k::sourceGen::replaceScripts::frames();
		GRRLIB_Render();
        rotate+=0.3f;
    }
	GRRLIB_Exit();
	exit(0);
}