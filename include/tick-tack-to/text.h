#ifndef TICK_FONTS
#define TICK_FONTS
#include "utils.h"
#include "basics.h"

typedef struct {
	u32 maxChar;
	u32 size;

	u32 scalex , scaley;
	u32 linegap;	
	TickTexture2D texture;
	
	struct {
		u32 w, h,yoffset;
		u32 tcx,tcy;

	} *CharcturesArray;
	u32 cl;	
}TickFont;



void SetDefaultFont(TickFont* font);
TickFont GetDefaultFont();

TickFont LoadFont(const char* filen,u32 scale, Vec4c cl);
TickFont LoadFont_ctx(const char* filen,u32 scale,Vec4c cl,TickContext* ctx);
TickFont LoadMemFont(void* fontData, u32 size, u32 scale , Vec4c cl);
TickFont LoadMemFont_ctx(void* fontData,u32 size, u32 scale , Vec4c cl,TickContext* ctx);


void DeleteFont(TickFont*font);
void DeleteFont_ctx(TickFont*font,TickContext*ctx);
void SetTabSpaces(u32 tabs);



void GetTextDemensions(const char* text, u32* w, u32* h);
void GetFontTextDemensions(const char* text, TickFont font,u32* w, u32* h);

void GetTextDemensionsExtended(const char* text,u32 xppading, u32 ypadding, u32* w, u32* h);
void GetFontTextDemensionsExtended(const char* text, TickFont font, u32 xpadding, u32 ypadding ,u32* w, u32* h);


void GetTextDemensionsSize(const char* text , u32 textSize, u32* w, u32* h);
void GetFontTextDemensionsSize(const char* text , u32 textSize, TickFont font,u32* w, u32* h);

void GetTextDemensionsExtendedSize(const char* text , u32 textSize,u32 xppading, u32 ypadding, u32* w, u32* h);
void GetFontTextDemensionsExtendedSize(const char* text , u32 textSize, TickFont font, u32 xpadding, u32 ypadding ,u32* w, u32* h);

void GetCharDemensions(u32 c, u32* w, u32* h);
void GetFontCharDemensions(u32 c,  TickFont font ,u32* w, u32* h);




void DrawText(const char* text , u32 x, u32 y);
void DrawText_ctx(const char* text , u32 x, u32 y,TickContext* ctx);

void DrawTextExtended(const char* text , u32 x, u32 y,u32 xpaading ,u32 ypadding );
void DrawTextExtended_ctx(const char* text , u32 x, u32 y,u32 xpaading ,u32 ypadding ,TickContext* ctx);

void DrawTextFont(const char* text , u32 x, u32 y,TickFont font);
void DrawTextFont_ctx(const char* text , u32 x, u32 y,TickFont font,TickContext* ctx);

void DrawTextFontExtended(const char* text , u32 x, u32 y,u32 xpaading ,u32 ypadding ,TickFont font);
void DrawTextFontExtended_ctx(const char* text , u32 x, u32 y,u32 xpaading ,u32 ypadding ,TickFont font,TickContext* ctx);

void DrawTextSegment(const char* text , u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h);
void DrawTextSegment_ctx(const char* text , u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h,TickContext* ctx);

void DrawTextSegmentExtended(const char* text , u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h,u32 xpadd, u32 ypadd);
void DrawTextSegmentExtended_ctx(const char* text , u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h , u32 xpadd, u32 ypadd,TickContext* ctx);

void DrawTextSegmentExtendedFont(const char* text , u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h, u32 xpadd , u32 ypadd , TickFont font);
void DrawTextSegmentExtendedFont_ctx(const char* text , u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h,
		u32 xpadd, u32 ypadd , TickFont font,TickContext* ctx);




void DrawTextSize(const char* text, u32 size, u32 x, u32 y);
void DrawTextSize_ctx(const char* text, u32 size, u32 x, u32 y,TickContext* ctx);

void DrawTextExtendedSize(const char* text, u32 size, u32 x, u32 y,u32 xpaading ,u32 ypadding );
void DrawTextExtendedSize_ctx(const char* text, u32 size, u32 x, u32 y,u32 xpaading ,u32 ypadding ,TickContext* ctx);

void DrawTextFontSize(const char* text, u32 size, u32 x, u32 y,TickFont font);
void DrawTextFontSize_ctx(const char* text, u32 size, u32 x, u32 y,TickFont font,TickContext* ctx);

void DrawTextFontExtendedSize(const char* text, u32 size, u32 x, u32 y,u32 xpaading ,u32 ypadding ,TickFont font);
void DrawTextFontExtendedSize_ctx(const char* text, u32 size, u32 x, u32 y,u32 xpaading ,u32 ypadding ,TickFont font,TickContext* ctx);

void DrawTextSegmentSize(const char* text, u32 size, u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h);
void DrawTextSegmentSize_ctx(const char* text, u32 size, u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h,TickContext* ctx);

void DrawTextSegmentExtendedSize(const char* text, u32 size, u32 x, u32 y , u32 xx , u32 yy , u32 w , u32 h,u32 xpadd, u32 ypadd);
void DrawTextSegmentExtendedSize_ctx(const char* text, u32 size, u32 x, u32 y ,
		u32 xx , u32 yy , u32 w , u32 h , u32 xpadd, u32 ypadd,TickContext* ctx);

void DrawTextSegmentExtendedFontSize(const char* text ,u32 size, u32 x, u32 y ,
					u32 xx , u32 yy ,
					u32 w , u32 h,
					u32 xpadd, u32 ypadd ,
					TickFont font);

void DrawTextSegmentExtendedFontSize_ctx(const char* text,u32 size , u32 x, u32 y ,
					u32 xx , u32 yy ,
					u32 w , u32 h,
					u32 xpadd, u32 ypadd ,
					TickFont font,TickContext* ctx);

#endif
