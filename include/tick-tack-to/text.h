#ifndef TICK_FONTS
#define TICK_FONTS
#include "utils.h"
#include "basics.h"
typedef struct {
	Vec2i dementions;
	u32 maxChar;
	u32 *fontTextureArray;
	u32 cl;	
}TickFont;


void SetDefaultFont(TickFont* font);
void DeleteFont(TickFont*font);
void DeleteFont_ctx(TickFont*font,TickContext*ctx);
void DrawText(const char* text , float x, float y);
void DrawText_WH(const char* text , float x, float y , float w , float h);
#endif
