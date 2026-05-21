#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "externel/stb_image.h"
#include "utils.h"
#include "texture.hpp"

Texture::Texture(unsigned char* data ,  unsigned int w , unsigned int h,unsigned int bpp){
	CHECK_GL_ERORR(glGenTextures(1, &m_texturID));
	CHECK_GL_ERORR(glBindTexture(GL_TEXTURE_2D, m_texturID));
	//Binde();
	CHECK_GL_ERORR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	CHECK_GL_ERORR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	CHECK_GL_ERORR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	CHECK_GL_ERORR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	this->m_data = data;
	this->m_w=w,this->m_h=h;
	this->m_bpp=bpp;
	this->m_dataS=m_h*m_w*m_bpp;
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA8, (int)m_w, (int)m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
	UnBinde();
	return;
}


Texture::~Texture(){
	if(!m_texturID){Eloge("Deleting a un decleared texture");return;}
	CHECK_GL_ERORR(glDeleteTextures(1, &m_texturID));
	return;
}

void Texture::Binde(unsigned int slot){
	if(!m_texturID){Eloge("Binding a un decleared texture");return;}
	CHECK_GL_ERORR(glActiveTexture(GL_TEXTURE0+slot/*+slot&0x1F*/));
	CHECK_GL_ERORR(glBindTexture(GL_TEXTURE_2D, m_texturID));
}
void Texture::UnBinde(){
	if(!m_texturID){Eloge("UnBinding a un decleared texture");return;}
	CHECK_GL_ERORR(glBindTexture(GL_TEXTURE_2D, 0));
	return;
}







ImageTexture::ImageTexture(std::string path):m_path(path){
	stbi_set_flip_vertically_on_load(1);
	this->image = stbi_load((const char*)m_path.c_str(), (int*)&m_w, (int*)&m_h, (int*)&m_bpp, (int)4);
		
	this->m_texture= new Texture(this->image,m_w,m_h,m_bpp);

	stbi_image_free(image);
}
ImageTexture::~ImageTexture(){delete m_texture;return;}


void ImageTexture::Binde(unsigned int slot){
	m_texture->Binde(slot);
}

void ImageTexture::UnBinde(){
	m_texture->UnBinde();
}

