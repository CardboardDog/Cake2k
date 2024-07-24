#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "Materials.hpp"
#include "Dummy.hpp"
#include "Models.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include <vector>
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
    namespace scenes{
        using namespace cake2k::assetGen::loadAssets::scenes::defines;
    }
}
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
namespace scene{
    std::vector<Object*> sceneObjects;
    void clearObjects(){
        for(unsigned int i=0;i<sceneObjects.size();i++){
            delete sceneObjects[i];
        }
        sceneObjects.clear();
    }
    void load(Scene scene){
        clearObjects();
        switch(scene){
            cake2k::assetGen::loadAssets::scenes::load();
            default:
                break;
        }
    }
}
namespace scripts{
    using namespace cake2k::sourceGen::replaceScripts::namespaces;
}
int main(void){
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
        GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);
        GRRLIB_3dMode(0.1,1000,45,1,0);// borrowed from GRRLIB examples :)
        for(unsigned int gameObject=0;gameObject<scene::sceneObjects.size();gameObject++){
            scene::sceneObjects[gameObject]->draw();
        }
        cake2k::sourceGen::replaceScripts::frames();
		GRRLIB_Render();
    }
	GRRLIB_Exit();
	exit(0);
}