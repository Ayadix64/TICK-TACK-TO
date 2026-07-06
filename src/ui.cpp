#include "../include/tick-tack-to.h"
#include "utils.h"

extern "C" TickContext g_defultContext;

#define DEF_XPADD 1
#define DEF_YPADD 4


Vec4c g_defaultBackgroundColour;
Vec4c g_defaultSlecetColour;
Vec4c g_defaultHoverColour;




enum TickEventSource{
	BUTTON,
	TEXTBOX,
	CHECKBOX,
};



void SetDefaultUIColors(){
	g_defaultBackgroundColour = UI_DEFAULT_BACKGROUND_COLOR;
	g_defaultHoverColour      = UI_DEFAULT_HOUVER_COLOR;
	g_defaultSlecetColour     = UI_DEFAULT_HOUVER_COLOR;

};

void InitUI(){
	SetDefaultUIColors();
}


bool IsSlected(TickContext* ctx){
	return ctx->selectID==ctx->selectCount;
}

void UpdateSelect(bool selected, bool highlited,TickContext* ctx){
	if(selected){
		ctx->selectID=ctx->selectCount;
	}
	if(highlited){
		ctx->highlightedElement=ctx->samplerCount;
	}
	ctx->selectCount++;
}



char DrawButtonPos(const char* text,float x , float y ){
	void SetDefaultUIColors();
	bool preased = false;
	bool highlited=false;
	bool slected = IsSlected(&g_defultContext);
	if(slected){highlited=true;};
	if(preased){
		slected=true;
	}
	u32 w , h;
	GetTextDemensionsExtended(text,DEF_XPADD,DEF_YPADD,&w, &h);

	DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultBackgroundColour);
	DrawTextExtended(text, x+15,  y+15,0,0);
	UpdateSelect(preased, highlited, &g_defultContext);
	return preased;
}
