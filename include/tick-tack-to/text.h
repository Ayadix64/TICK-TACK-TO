#ifndef TICK_FONTS
#define TICK_FONTS
#include "utils.h"
#include "basics.h"
typedef struct {
	u32 maxChar;
	u32 size;

	float scalex , scaley;
	u32 linegap;	
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

void GetTextDemensions(const char* text, u32* w, u32* h);
void GetFontTextDemensions(const char* text, TickFont font,u32* w, u32* h);

void DeleteFont(TickFont*font);
void DeleteFont_ctx(TickFont*font,TickContext*ctx);


void DrawText(const char* text , float x, float y);
void DrawText_ctx(const char* text , float x, float y,TickContext* ctx);

void DrawTextFont(const char* text , float x, float y,TickFont font);
void DrawTextFont_ctx(const char* text , float x, float y,TickFont font,TickContext* ctx);

#endif
