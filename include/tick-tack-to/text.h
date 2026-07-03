#ifndef TICK_FONTS
#define TICK_FONTS
#include "utils.h"
#include "basics.h"
typedef struct {
	u32 maxChar;
	u32 scale;
	TickTexture2D texture;
	
	struct {
		u32 w, h,yoffset;
		u32 tcx;

	} *CharcturesArray;
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
