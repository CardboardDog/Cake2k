typedef struct{
    //Texture* texture;
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

}