#ifndef TICK_FONTS
#define TICK_FONTS
#include "utils.h"
#include "basics.h"
typedef struct {
	Vec2i dementions;
	u32 maxChar;
	struct {
		TickTexture2D texture;
		u32 w, h;
	} *fontTextureArray;
	u32 cl;	
}TickFont;


void SetDefaultFont(TickFont* font);

TickFont LoadFont(const char* filen,u32 scale, Vec4c cl);
TickFont LoadFont_ctx(const char* filen,u32 scale,Vec4c cl,TickContext* ctx);
TickFont LoadMemFont(void* fontData, u32 size, u32 scale , Vec4c cl);
TickFont LoadMemFont_ctx(void* fontData,u32 size, u32 scale , Vec4c cl,TickContext* ctx);

void DeleteFont(TickFont*font);
void DeleteFont_ctx(TickFont*font,TickContext*ctx);

void DrawText(const char* text , float x, float y);
void DrawText_WH(const char* text , float x, float y , float w , float h);
#endif
