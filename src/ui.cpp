#include "utils.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../include/tick-tack-to.h"
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
	       GetMousePos().y>=y && GetMousePos().y <= y+h && !(GetMouseClickes()&(1<<3));
}
bool Hover_ctx(u32 x , u32 y , u32 w , u32 h, TickContext* ctx){
	
	return GetMousePos_ctx(ctx).x>=x && GetMousePos_ctx(ctx).x <=w+x &&
	       GetMousePos_ctx(ctx).y>=y && GetMousePos_ctx(ctx).y <= y+h && !(GetMouseClickes_ctx(ctx)&(1<<3));
}


bool Clicked(u32 x , u32 y , u32 w , u32 h){
	return GetMousePos().x>=x && GetMousePos().x <=w+x &&
	       GetMousePos().y>=y && GetMousePos().y <= y+h && GetMouseClickes()&(1<<3);
}
bool Clicked_ctx(u32 x , u32 y , u32 w , u32 h, TickContext* ctx){
	
	return GetMousePos_ctx(ctx).x>=x && GetMousePos_ctx(ctx).x <=w+x &&
	       GetMousePos_ctx(ctx).y>=y && GetMousePos_ctx(ctx).y <= y+h && GetMouseClickes_ctx(ctx)&(1<<3);
}

bool ClickedAndReleased(u32 x , u32 y , u32 w , u32 h){
	return GetMousePos().x>=x && GetMousePos().x <=w+x &&
	       GetMousePos().y>=y && GetMousePos().y <= y+h && GetMouseClickes()&1;
}
bool ClickedAndReleased_ctx(u32 x , u32 y , u32 w , u32 h, TickContext* ctx){
	
	return GetMousePos_ctx(ctx).x>=x && GetMousePos_ctx(ctx).x <=w+x &&
	       GetMousePos_ctx(ctx).y>=y && GetMousePos_ctx(ctx).y <= y+h && GetMouseClickes_ctx(ctx)&1;
}

bool DoubleClicked(u32 x , u32 y , u32 w , u32 h){
	return GetMousePos().x>=x && GetMousePos().x <=w+x &&
	       GetMousePos().y>=y && GetMousePos().y <= y+h && GetMouseClickes()&(1<<3);
}
bool DoubleClicked_ctx(u32 x , u32 y , u32 w , u32 h, TickContext* ctx){
	return GetMousePos_ctx(ctx).x>=x && GetMousePos_ctx(ctx).x <=w+x &&
	       GetMousePos_ctx(ctx).y>=y && GetMousePos_ctx(ctx).y <= y+h && GetMouseClickes_ctx(ctx)&(1<<3);
}





char Button(const char* text,float x , float y ){
	char preased = false;
	bool highlited=false;
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	
	u32 w , h;

	GetTextDemensionsExtended(text,DEF_XPADD,DEF_YPADD,&w, &h);
	if(slected){
		DrawEmptyRoundedRectangel(x-1, y-1, w + (32), h + (32), 10,2 ,90,  g_defaultHoverColour);

	}

	if(Hover(x, y, w+30, h+30)){
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultHoverColour);
		preased|=2;
	}
	else if(Clicked(x, y, w+30, h+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultSlecetColour);
		preased|=2;
		
	}
	if(ClickedAndReleased( x, y, w+30, h+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultSlecetColour);
		preased|=1;
	}
	if(!preased) {
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultBackgroundColour);

	}
	
	if(!Clicked( x, y, w+30, h+30)&& GetMouseClickes()&1 && slected){
		DiscardSelect(&g_defaultContext);
		slected=false;
	}
	if(preased&1){slected=1;}	
	DrawTextExtended(text, x+15,  y+15,DEF_XPADD,DEF_YPADD);

	UpdateSelect(slected&1, highlited, &g_defaultContext);
	return preased;
}




char ButtonColor(const char* text,float x , float y , Vec4c bg , Vec4c hoverbg , Vec4c slectbg ){
	char preased = false;
	bool highlited=false;
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	u32 w , h;
	GetTextDemensionsExtended(text,DEF_XPADD,DEF_YPADD,&w, &h);
	
	if(slected){
		DrawEmptyRoundedRectangel(x-1, y-1, w + (32), h + (32), 10,2, 90,  hoverbg);

	}

	if(Hover(x, y, w+30, h+30)){
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, hoverbg);
		preased|=2;
	}
	else if(Clicked(x, y, w+30, h+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, slectbg);
		if(ClickedAndReleased( x, y, w+30, h+30)){
			preased|=1;
		}	
	}
	if(ClickedAndReleased( x, y, w+30, h+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, g_defaultSlecetColour);
		preased|=1;
	}
	if(!preased) {
		DrawRoundedRectangel(x, y, w + (30), h + (30), 10, 90, bg);
	}
	
	if(!preased&& GetMouseClickes()&1 && slected){
		DiscardSelect(&g_defaultContext);
		slected=false;
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
	tbd->usedsize=0;
	memset(tbd->data, 0, tbd->size);
}



char TextBox(float x , float y , float w, TextBoxData* tbd){
	char preased = false;
	bool highlited=false;
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	
	u32 th=GetDefaultFont().linegap;
	
	if(slected){
		DrawRoundedRectangel(x-1, y-1, w+2, th +30+2, 10, 90,  g_defaultHoverColour);

	}

	if(Hover(x, y, w, th+30)){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, g_defaultHoverColour);
		preased|=2;
	}
	else if(Clicked(x, y, w, th+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, g_defaultSlecetColour);	
		preased|=2;
	}
	if(ClickedAndReleased( x, y, w+30, th+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, g_defaultSlecetColour);
		preased|=1;
	}
	if(!preased){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, g_defaultBackgroundColour);
	}
	
	if(preased&1){slected=1;}	
	if(!preased&& GetMouseClickes()&1 && slected){
		DiscardSelect(&g_defaultContext);
		slected=false;
	}
	UpdateSelect(slected, highlited, &g_defaultContext);
	

	
	u32 curserpos ;
	GetTextDemensionsExtendedSize(tbd->data, tbd->pos, DEF_XPADD, DEF_YPADD, &curserpos, 0);

	if((g_defaultContext.lastkey>=32 || g_defaultContext.lastkey=='\t') && tbd->size < tbd->maxsize && slected){
		size_t sz=tbd->size,usz=tbd->usedsize;
		tbd->data=(char*)PushChar(g_defaultContext.lastkey, tbd->pos, &sz, (size_t*)&usz, tbd->data);
		tbd->size=sz;
		tbd->usedsize=usz;
		tbd->pos++;
		u32 cw;
		GetCharDemensions(g_defaultContext.lastkey, &cw, 0);
		if(curserpos+cw+30> w){
			tbd->xoffset+=cw+DEF_XPADD;
		}
		curserpos+=cw+DEF_XPADD;
	}
	
	if(IsKeyPreased(GLFW_KEY_BACKSPACE) && tbd->pos&& slected){
		size_t usz=tbd->usedsize;
		
		tbd->pos--;
		PopChar(tbd->pos, &usz, tbd->data);
		tbd->usedsize=usz;
		u32 cw;
		GetCharDemensions(tbd->data[tbd->pos], &cw, 0);
		if( tbd->xoffset){
			tbd->xoffset-=(cw+DEF_XPADD);
		}else if(curserpos){}
			curserpos-=cw+DEF_XPADD;
		
	}
 	
	if(IsKeyPreased(GLFW_KEY_LEFT) && tbd->pos && slected){
		tbd->pos--;
		u32 cw;
		GetCharDemensions(tbd->data[tbd->pos], &cw, 0);
		if( (curserpos-tbd->xoffset)<=0){
			tbd->xoffset-=(cw+DEF_XPADD);
		}else if(curserpos){
			curserpos-=cw+DEF_XPADD;
		}
	}
	
	if(IsKeyPreased(GLFW_KEY_RIGHT) && tbd->pos < tbd->usedsize && slected){
		tbd->pos++;
		u32 cw;
		GetCharDemensions(tbd->data[tbd->pos], &cw, 0);
		if( (curserpos-tbd->xoffset)+30>=w){
			tbd->xoffset+=(cw+DEF_XPADD);
		}else if(curserpos){
			curserpos+=cw+DEF_XPADD;
		}
	}
	



	if(slected){
		if((u64)(glfwGetTime()*2.0)%2){ //aka; flicker evry half a secend
			DrawRectangel(x+15+curserpos-tbd->xoffset, y+13, DEF_XPADD, th+4, {200,200,255,255});
		}	
	}else {
		DrawRectangel(x+15+curserpos-tbd->xoffset, y+13, DEF_XPADD, th+4, {200,200,255,255}); //the cusrsure
	}
	DrawTextSegmentExtendedSize(tbd->data, tbd->usedsize, x+15-tbd->xoffset, y+15, tbd->xoffset, 0, w-30, th,DEF_XPADD,DEF_YPADD);
	

	
	return preased;
}







void CheckBox(const char* bx ,float x , float y , char * b){
	char preased = false;
	bool highlited=false;
	
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	
	u32 th=GetDefaultFont().linegap;
	
	if(slected){
		DrawRoundedRectangel(x-1, y-1, th+2, th+2, 10, 90,  g_defaultHoverColour);

	}

	if(Hover(x, y, th, th)){
		DrawRoundedRectangel(x, y, th , th, 10, 90, g_defaultHoverColour);
		preased|=2;
	}
	else if(Clicked(x, y, th, th) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, th ,th, 10, 90, g_defaultSlecetColour);
		
		if(ClickedAndReleased( x, y, th, th)){
			preased|=1;
		}	
	}
	if(!preased){
		DrawRoundedRectangel(x, y, th , th , 10, 90, g_defaultBackgroundColour);
	}
	
	if(preased&1){slected=1;}	
	if(!preased&& GetMouseClickes()&1 && slected){
		DiscardSelect(&g_defaultContext);
		slected=false;
	}
	UpdateSelect(slected, highlited, &g_defaultContext);
	

	DrawTextExtended(bx, x+th, y, DEF_XPADD, DEF_XPADD);
	if(preased){
		*b=!*b;
	}

	
	return;
}



