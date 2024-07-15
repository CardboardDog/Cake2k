#include "Textures.hpp"
#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>
typedef struct{
    Texture** texture;
    unsigned char shine; // ignored on psp, this is for later plans
    bool smooth;
    bool filter; // linear filtering
    bool lit; // is it shaded?
    bool shadows; // not on psp
    bool cast; //also^^^ ^^ ^^^
    bool celshaded; // another maybe
    bool mipmaps; // ignored for now, maybe later
}Material;
void useMaterial(Material* mat){
    if(mat->lit){
        if(mat->smooth){
            sceGuShadeModel(GU_SMOOTH);
        }else{
            sceGuShadeModel(GU_FLAT);
        }
    }
    sceGuTexMode(GU_PSM_4444,0,0,1);
    sceGuTexFunc(GU_TFX_MODULATE,GU_TCC_RGBA);
    if(mat->filter){
        sceGuTexFilter(GU_NEAREST,GU_LINEAR);
    }else{
        sceGuTexFilter(GU_NEAREST,GU_NEAREST);
    }
    sceGuTexImage(
        0,
        mat->texture->sqWidth,
        mat->texture->sqHeight,
        mat->texture->sqWidth,
        mat->texture->data
    );
}