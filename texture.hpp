#ifndef TICK_TEXTURE
#define TICK_TEXTURE
#include <string>
class Texture {
private:
	unsigned int m_texturID=0;
	unsigned char* m_data = nullptr;
	unsigned int m_dataS = 0;
	
	unsigned int m_w=0,m_h,m_bpp=0;
public:
	Texture(unsigned char* data,  unsigned int width, unsigned int heigth, unsigned int bpp);
	~Texture();
	void Binde(unsigned int slot = 0);
	void UnBinde();
};


class ImageTexture{
private:
	Texture* m_texture;
	std::string m_path;
	unsigned int m_w=0,m_h=0,m_bpp=0;
	unsigned char* image = nullptr;
	
public:
	ImageTexture(std::string path);
	~ImageTexture();
	void Binde(unsigned int slot=0);
	void UnBinde();
	
};

#endif
