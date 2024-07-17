#include <grrlib.h>
typedef struct{
    #ifdef CAKE2K_WII
    GRRLIB_texImg* texture;
    #endif
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
    GRRLIB_SetTexture(mat->texture,TRUE);
    //if(mat->shine>4)GRRLIB_SetLightSpec(0,(guVector){0.0f,0.0f,0.0f},(int)mat->shine,0xFFFF,0xFFFFFFFF);
}