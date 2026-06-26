#ifndef TICK_TEXTURE
#define TICK_TEXTURE
#include "utils.h"
u32 GenTexture();

void SetTextureData(u8* data, u32 w,u32 h, u32 bpp);
void SetTexturDataFromeFile(const char* fileName);
void BindTexture(u32 texture, u8 slot);
void DeletTexture(u32* texture);


#endif
