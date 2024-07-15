#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <pspgu.h>
#include <pspgum.h>
#include <malloc.h>
#include <pspdisplay.h>
#include <pspkernel.h>
typedef struct{
    unsigned int width, height;
    unsigned int sqWidth, sqHeight;
    void* data;
}Texture;
/*
    These functions are
    under the MIT License, 
    https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master?tab=MIT-1-ov-file#readme
*/
#ifdef CAKE2K_TARGET_PSP
unsigned int pow2(const unsigned int value){
    unsigned int poweroftwo = 1;
    while (poweroftwo < value) {
        poweroftwo <<= 1;
    }
    return poweroftwo;
}
void copy_texture_data(void* dest, const void* src, const int pW, const int width, const int height){
    for (unsigned int y = 0; y < (unsigned)height; y++) {
        for (unsigned int x = 0; x < (unsigned)width; x++) {
            ((unsigned int*)dest)[x + y * pW] = ((unsigned int *)src)[x + y * width];
        }
    }
}
void swizzle_fast(u8 *out, const u8 *in, const unsigned int width, const unsigned int height){
    unsigned int blockx, blocky;
    unsigned int j;

    unsigned int width_blocks = (width / 16);
    unsigned int height_blocks = (height / 8);

    unsigned int src_pitch = (width - 16) / 4;
    unsigned int src_row = width * 8;

    const u8 *ysrc = in;
    u32 *dst = (u32 *)out;

    for (blocky = 0; blocky < height_blocks; ++blocky){
        const u8 *xsrc = ysrc;
        for (blockx = 0; blockx < width_blocks; ++blockx){
            const u32 *src = (u32 *)xsrc;
            for (j = 0; j < 8; ++j) {
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                src += src_pitch;
            }
            xsrc += 16;
        }
        ysrc += src_row;
    }
}
static unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm){
	switch (psm)
	{
		case GU_PSM_T4:
			return (width * height) >> 1;

		case GU_PSM_T8:
			return width * height;

		case GU_PSM_5650:
		case GU_PSM_5551:
		case GU_PSM_4444:
		case GU_PSM_T16:
			return 2 * width * height;

		case GU_PSM_8888:
		case GU_PSM_T32:
			return 4 * width * height;

		default:
			return 0;
	}
}
void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm){
	static unsigned int staticOffset = 0;
	unsigned int memSize = getMemorySize(width,height,psm);
	void* result = (void*)staticOffset;
	staticOffset += memSize;

	return result;
}
void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm){
	void* result = getStaticVramBuffer(width,height,psm);
	return (void*)(((unsigned int)result) + ((unsigned int)sceGeEdramGetAddr()));
}
Texture* loadTexture(const char* filename, const int vram){
    int width, height, nrChannels;    
    stbi_set_flip_vertically_on_load(GU_TRUE);
    unsigned char *data = stbi_load(filename, &width, &height,
                                    &nrChannels, STBI_rgb_alpha);
    if(!data)
        return NULL;
    Texture* tex = (Texture*)malloc(sizeof(Texture));
    tex->width = width;
    tex->height = height;
    tex->sqWidth = pow2(width);
    tex->sqHeight = pow2(height);
    unsigned int *dataBuffer =
        (unsigned int *)memalign(16, tex->sqHeight * tex->sqWidth * 4);
    copy_texture_data(dataBuffer, data, tex->sqWidth, tex->width, tex->height);
    stbi_image_free(data);
    unsigned int* swizzled_pixels = NULL;
    size_t size = tex->sqHeight * tex->sqWidth * 4;
    if(vram){
        swizzled_pixels = (unsigned int*)getStaticVramTexture(tex->sqWidth, tex->sqHeight, GU_PSM_8888);
    } else {
        swizzled_pixels = (unsigned int *)memalign(16, size);
    }
    swizzle_fast((u8*)swizzled_pixels, (const u8*)dataBuffer, tex->sqWidth * 4, tex->sqHeight);
    free(dataBuffer);
    tex->data = swizzled_pixels;
    sceKernelDcacheWritebackInvalidateAll();
    return tex;
}
#endif