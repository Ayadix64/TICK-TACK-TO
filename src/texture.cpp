#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "externel/stb_image.h"
#include "utils.h"
#include "texture.hpp"

u32 GenTexture(){
	u32 texture;
	CHECK_GL_ERORR(glGenTextures(1, &texture));
	CHECK_GL_ERORR(glBindTexture(GL_TEXTURE_2D, texture));
	CHECK_GL_ERORR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	CHECK_GL_ERORR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	CHECK_GL_ERORR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	CHECK_GL_ERORR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	return texture;
}

void SetTextureData(u8 *data, u32 w, u32 h){
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA8, (int)w, (int)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	return;
}
void SetTexturDataFromeFile(const char* fileName){
	stbi_set_flip_vertically_on_load(1);
	int w,h,bpp;
	u8* pb = stbi_load((const char*)fileName, (int*)&w, (int*)&h, (int*)&bpp, (int)4);
	if(!pb){
		Eloge("Cant Load "+ std::string(fileName)+" , "+std::string(stbi_failure_reason()));
		return;
	}	
	if(bpp != 4){
		Eloge("Image BPP != 4");//bruh
		return;
	}
	SetTextureData(pb, w, h);

	stbi_image_free(pb);
	return;
}

void BindTexture(u32 texture, u8 slot){
	CHECK_GL_ERORR(glActiveTexture(GL_TEXTURE0+(slot&0x1f)));
	CHECK_GL_ERORR(glBindTexture(GL_TEXTURE_2D, texture));
}

void DeletTexture(u32* texture){
	CHECK_GL_ERORR(glDeleteTextures(1, texture));
	return;
}
