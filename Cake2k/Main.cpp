#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "Materials.hpp"
#include "Dummy.hpp"
#include "Models.hpp"
namespace assets{
    namespace textures{
        using namespace cake2k::assetGen::loadAssets::textures::defines;
    }
    namespace materials{
        using namespace cake2k::assetGen::loadAssets::materials::defines;
    }
    namespace models{
        using namespace cake2k::assetGen::loadAssets::models::defines;
    }
}
using namespace cake2k::sourceGen::replaceScripts::namespaces;
using namespace cake2k::assetGen::loadAssets::models::renderers;
namespace settings{
    namespace global{
        // no global settings yet
    }
    namespace scene{
        namespace fog{
            f32 start;
            f32 end;
            GXColor color;
            bool enabled;
        }
        namespace bloom{
            int focus;
            int intensity;
            int threshold;
            bool enabled;
        }
        namespace sun{
            u32 color = 0x000000FF;
            float rotation[2] = {0.0f,0.0f};
        }
    }
}
int main(void){
    float rotate = 0;
	GRRLIB_Init();
	WPAD_Init();
    cake2k::assetGen::loadAssets::textures::load();
    cake2k::assetGen::loadAssets::materials::load();
    cake2k::assetGen::loadAssets::models::load();
	cake2k::sourceGen::replaceScripts::starts();
    while(1){
		WPAD_ScanPads();
		GRRLIB_SetBackgroundColour(255,85,10,0xFF);
		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;
        GRRLIB_3dMode(0.1,1000,45,1,0);// borrowed from GRRLIB examples :)
        GRRLIB_ObjectView(0,0,-30,rotate,rotate*2,rotate*3,1,1,1);
        assets::models::cubeThing->draw();
        cake2k::sourceGen::replaceScripts::frames();
		GRRLIB_Render();
        rotate+=0.3f;
    }
	GRRLIB_Exit();
	exit(0);
}