#include "../include/tick-tack-to.h"
#include "utils.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" TickContext g_defaultContext;

#define DEF_XPADD 1
#define DEF_YPADD 4


Vec4c g_defaultBackgroundColour;
Vec4c g_defaultSlecetColour;
Vec4c g_defaultHoverColour;
u32 g_Roundness=30;



enum TickEventSource{
	BUTTON,
	TEXTBOX,
	CHECKBOX,
};



void SetDefaultUIColors(){
	g_defaultBackgroundColour = UI_DEFAULT_BACKGROUND_COLOR;
	g_defaultHoverColour      = UI_DEFAULT_HOUVER_COLOR;
	g_defaultSlecetColour     = UI_DEFAULT_SELECT_COLOR;

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

void DiscardSelect(TickContext* ctx){
	ctx->selectID=-1;
}


bool Hover(u32 x , u32 y , u32 w , u32 h){
	return GetMousePos().x>=x && GetMousePos().x <=w+x &&
	       GetMousePos().y>=y && GetMousePos().y <= y+h && !GetMouseClickes();
}
bool Hover_ctx(u32 x , u32 y , u32 w , u32 h, TickContext* ctx){
	
	return GetMousePos_ctx(ctx).x>=x && GetMousePos_ctx(ctx).x <=w+x &&
	       GetMousePos_ctx(ctx).y>=y && GetMousePos_ctx(ctx).y <= y+h && !GetMouseClickes_ctx(ctx);
}


bool Clicked(u32 x , u32 y , u32 w , u32 h){
	return GetMousePos().x>=x && GetMousePos().x <=w+x &&
	       GetMousePos().y>=y && GetMousePos().y <= y+h && GetMouseClickes()&1;
}
bool Clicked_ctx(u32 x , u32 y , u32 w , u32 h, TickContext* ctx){
	
	return GetMousePos_ctx(ctx).x>=x && GetMousePos_ctx(ctx).x <=w+x &&
	       GetMousePos_ctx(ctx).y>=y && GetMousePos_ctx(ctx).y <= y+h && GetMouseClickes_ctx(ctx)&1;
}

bool DoubleClicked(u32 x , u32 y , u32 w , u32 h){
	return GetMousePos().x>=x && GetMousePos().x <=w+x &&
	       GetMousePos().y>=y && GetMousePos().y <= y+h && GetMouseClickes()&(1<<2);
}
bool DoubleClicked_ctx(u32 x , u32 y , u32 w , u32 h, TickContext* ctx){
	return GetMousePos_ctx(ctx).x>=x && GetMousePos_ctx(ctx).x <=w+x &&
	       GetMousePos_ctx(ctx).y>=y && GetMousePos_ctx(ctx).y <= y+h && GetMouseClickes_ctx(ctx)&(1<<2);
}





char Button(const char* text,float x , float y ){
	char preased = false;
	bool highlited=false;
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	if(preased){
		slected=true;
	}
	u32 w , h;
	
	GetTextDemensionsExtended(text,DEF_XPADD,DEF_YPADD,&w, &h);
	

	if(Hover(x, y, w+30, h+30) || (slected && !IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultHoverColour);
		preased|=2;
	}
	else if(Clicked(x, y, w+30, h+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultSlecetColour);
		preased|=1;
	}
	else {
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultBackgroundColour);
		if(GetMouseClickes()&1){
			DiscardSelect(&g_defaultContext);
		}
	}
	if(preased&1){slected=1;}	
	DrawTextExtended(text, x+15,  y+15,DEF_XPADD,DEF_YPADD);

	UpdateSelect(slected&1, highlited, &g_defaultContext);
	return preased;
}


void InitTextBoxData(TextBoxData* tbd,u32 maxsize){
	tbd->size=1024;
	tbd->pos=0;
	tbd->maxsize=maxsize?maxsize:-1;
	tbd->flags={.EnableNumbers=1,.EnbleCharctures=1};
	tbd->xoffset=0;
	tbd->data=(char*)malloc(tbd->size);
	memset(tbd->data, 0, tbd->size);
}



char TextBox(float x , float y , float w, TextBoxData* tbd){
	char preased = false;
	bool highlited=false;
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	
	u32 tw, th;
	
	GetTextDemensionsExtended(tbd->data,DEF_XPADD,DEF_YPADD,&tw, &th);
	

	if(Hover(x, y, w, th+30)){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, g_defaultHoverColour);
		preased|=2;
	}
	else if(Clicked(x, y, w, th+30)||slected){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, g_defaultSlecetColour);
		preased|=1;
		slected=1;
	}
	else {
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, g_defaultBackgroundColour);
	}
	DrawTextSegmentExtended(tbd->data, x+15,  y+15,tbd->xoffset,0,w-30,th,DEF_XPADD,DEF_YPADD);
	u32 curserpos ;
	GetTextDemensionsExtendedSize(tbd->data, tbd->pos, DEF_XPADD, DEF_YPADD, &curserpos, 0);
	DrawRectangel(x+15+curserpos, y+13, DEF_XPADD, th+4, {200,200,255,255});
	if(slected&&g_defaultContext.lastkey){
			
	}	
	UpdateSelect(preased, highlited, &g_defaultContext);
	return preased;
}

