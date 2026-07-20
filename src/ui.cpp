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


bool Hover(int x , int y , int w , int h){
	return (int)GetMousePos().x>=x && (int)GetMousePos().x <=w+x &&
	       (int)GetMousePos().y>=y && (int)GetMousePos().y <= y+h && !(GetMouseClickes()&(1<<3));
}
bool Hover_ctx(int x , int y , int w , int h, TickContext* ctx){
	
	return (int)GetMousePos_ctx(ctx).x>=x && (int)GetMousePos_ctx(ctx).x <=w+x &&
	       (int)GetMousePos_ctx(ctx).y>=y && (int)GetMousePos_ctx(ctx).y <= y+h && !(GetMouseClickes_ctx(ctx)&(1<<3));
}


bool Clicked(int x , int y , int w , int h){
	return (int)GetMousePos().x>=x && (int)GetMousePos().x <=w+x &&
	       (int)GetMousePos().y>=y && (int)GetMousePos().y <= y+h && GetMouseClickes()&(1<<3);
}
bool Clicked_ctx(int x , int y , int w , int h, TickContext* ctx){
	
	return (int)GetMousePos_ctx(ctx).x>=x && (int)GetMousePos_ctx(ctx).x <=w+x &&
	       (int)GetMousePos_ctx(ctx).y>=y && (int)GetMousePos_ctx(ctx).y <= y+h && GetMouseClickes_ctx(ctx)&(1<<3);
}

bool ClickedAndReleased(int x , int y , int w , int h){
	return (int)GetMousePos().x>=x && (int)GetMousePos().x <=w+x &&
	       (int)GetMousePos().y>=y && (int)GetMousePos().y <= y+h && GetMouseClickes()&1;
}
bool ClickedAndReleased_ctx(int x , int y , int w , int h, TickContext* ctx){
	
	return (int)GetMousePos_ctx(ctx).x>=x && (int)GetMousePos_ctx(ctx).x <=w+x &&
	       (int)GetMousePos_ctx(ctx).y>=y && (int)GetMousePos_ctx(ctx).y <= y+h && GetMouseClickes_ctx(ctx)&1;
}

bool DoubleClicked(int x , int y , int w , int h){
	return (int)GetMousePos().x>=x && (int)GetMousePos().x <=w+x &&
	       (int)GetMousePos().y>=y && (int)GetMousePos().y <= y+h && GetMouseClickes()&(1<<3);
}
bool DoubleClicked_ctx(int x , int y , int w , int h, TickContext* ctx){
	return (int)GetMousePos_ctx(ctx).x>=x && (int)GetMousePos_ctx(ctx).x <=w+x &&
	       (int)GetMousePos_ctx(ctx).y>=y && (int)GetMousePos_ctx(ctx).y <= y+h && GetMouseClickes_ctx(ctx)&(1<<3);
}





char Button(const char* text,u32 x , u32 y ){
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




char ButtonColor(const char* text,u32 x , u32 y , Vec4c bg , Vec4c hoverbg , Vec4c slectbg ){
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
	
	if(!preased&& GetMouseClickes()&(1<<3) && slected){
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


char TextBoxColour(u32 x , u32 y , u32 w, TextBoxData* tbd, Vec4c bg, Vec4c hbg , Vec4c sbg, Vec4c cursurCl){
	char preased = false;
	bool highlited=false;
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	
	u32 th=GetDefaultFont().linegap;
	
	if(slected){
		DrawRoundedRectangel(x-1, y-1, w+2, th +30+2, 10, 90,  hbg);

	}

	if(Hover(x, y, w, th+30)){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, hbg);
		preased|=2;
	}
	else if(Clicked(x, y, w, th+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, sbg);	
		preased|=2;
	}
	if(ClickedAndReleased( x, y, w+30, th+30) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, sbg);
		preased|=1;
	}
	if(!preased){
		DrawRoundedRectangel(x, y, w , th + (30), 10, 90, bg);
	}
	
	if(preased&1){slected=1;}	
	if(!preased&& GetMouseClickes()&(1<<3) && slected){
		DiscardSelect(&g_defaultContext);
		slected=false;
	}
	UpdateSelect(slected, highlited, &g_defaultContext);
	

	
	u32 curserpos =0;
	GetTextDemensionsExtendedSize(tbd->data, tbd->pos, DEF_XPADD, DEF_YPADD, &curserpos, 0);
	
	/*
	DrawRectangel(x+15, y+15-th, curserpos, th, {200,200,0,255});
	
	DrawRectangel(x+15, y+th+15, tbd->xoffset, th, {70,70,70,255});
	DrawRectangel(x+15+tbd->xoffset, y+th+15, w-30, th, {200,0,0,255});

	DrawTextSegmentExtendedSize(tbd->data, tbd->usedsize, x+15, y+15+th, 0, 0, 3000, th,DEF_XPADD,DEF_YPADD);// */



	curserpos-=tbd->xoffset;
	

	
	if(slected){
		if((u64)(glfwGetTime()*4.0)%2){ //aka; flicker evry half a secend
			DrawRectangel(x+15+curserpos, y+13, DEF_XPADD, th+4, cursurCl);
		}	
	}else {
		DrawRectangel(x+15+curserpos, y+13, DEF_XPADD, th+4, {200,200,255,255}); //the cusrsure
	}
	DrawTextSegmentExtendedSize(tbd->data, tbd->usedsize, x+15-tbd->xoffset, y+15, tbd->xoffset, 0, w-30, th,DEF_XPADD,DEF_YPADD);


	if((g_defaultContext.key>=32 || g_defaultContext.key=='\t') && tbd->size < tbd->maxsize && slected){
		size_t sz=tbd->size,usz=tbd->usedsize;
		tbd->data=(char*)PushChar(g_defaultContext.key, tbd->pos, &sz, (size_t*)&usz, tbd->data);
		tbd->size=sz;
		tbd->usedsize=usz;
		tbd->pos++;
		u32 cw;
		GetCharDemensions(g_defaultContext.key, &cw, 0);
		if(curserpos+cw+30> w){
			tbd->xoffset+=cw+DEF_XPADD;
		}
	}else if(IsKeyPreased(GLFW_KEY_BACKSPACE) && tbd->pos&& slected){
		tbd->pos--;
		u32 cw;
		GetCharDemensions(tbd->data[tbd->pos], &cw, 0);
		
		if((int)(curserpos-(cw+DEF_XPADD)-w-30)<=0){	
			tbd->xoffset-= min((cw+DEF_XPADD),tbd->xoffset);
		}

		size_t usz=tbd->usedsize;
		PopChar(tbd->pos, &usz, tbd->data);
		tbd->usedsize=usz;
	}else if(IsKeyPreased(GLFW_KEY_LEFT) && tbd->pos && slected){
		
		tbd->pos--;
		u32 cw;
		
		GetCharDemensions(tbd->data[tbd->pos], &cw, 0);
		
		if((int)(curserpos-(cw+DEF_XPADD))<=0){
			tbd->xoffset-= min((cw+DEF_XPADD),tbd->xoffset); // so we are not sub zero
		}

		
	}else if(IsKeyPreased(GLFW_KEY_RIGHT) && tbd->pos < tbd->usedsize && slected){
		u32 cw;
		GetCharDemensions(tbd->data[tbd->pos], &cw, 0);
		
		tbd->pos++;
		if((int)(curserpos)>=(int)(w-cw-DEF_XPADD-30)){
			tbd->xoffset+=cw+DEF_XPADD;// so we are not sub zero
		}

	}
	


	
	return preased;
}


char TextBox(u32 x , u32 y , u32 w, TextBoxData* tbd){
	return TextBoxColour(x, y, w, tbd, g_defaultBackgroundColour, g_defaultHoverColour, g_defaultSlecetColour, {255,255,255,255});
}







void CheckBox(const char* bx ,u32 x , u32 y , char* b){
	char preased = false;
	bool highlited=false;
	
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	
	u32 th=GetDefaultFont().linegap;
	
	if(slected){
		DrawRoundedRectangel(x-1, y-1, th+2, th+2, 5, 90,  g_defaultHoverColour);

	}

	if(Hover(x, y, th, th) && !*b){
		DrawRoundedRectangel(x, y, th , th, 5, 90, g_defaultHoverColour);
		preased|=2;
	}
	else if(Clicked(x, y, th, th) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, th ,th, 5, 90, g_defaultSlecetColour);
		preased|=2;
		
	}
	if(ClickedAndReleased( x, y, th, th) || (slected && IsKeyPreased(GLFW_KEY_ENTER))){
		DrawRoundedRectangel(x, y, th ,th, 5, 90, g_defaultSlecetColour);
		preased|=1;
	}
	if(!preased){
		if(*b){
			DrawRoundedRectangel(x, y, th , th , 5, 90, g_defaultSlecetColour);
			//DrawLine({x,y+th/2}, {x+th/2,y+th}, 2, {255,255,255,255});	
			//DrawLine({x+th/2,y+th}, {x+th,y}, 2, {255,255,255,255});
		}else {
			DrawRoundedRectangel(x, y, th , th , 5, 90, g_defaultBackgroundColour);
		}
	}
	
	if(preased&1){slected=1;}	

	if(!preased&& GetMouseClickes()&(1<<3) && slected){
		DiscardSelect(&g_defaultContext);
		slected=false;
	}
	UpdateSelect(slected, highlited, &g_defaultContext);
	

	DrawTextExtended(bx, x+10+th, y, DEF_XPADD, DEF_XPADD);
	
	if(preased&1){
		*b=!*b;
	}

	
	return;
}


char Slider(u32 x , u32 y , u32 w,  float* s){
	char preased = false;
	bool highlited=false;
		
	bool slected = IsSlected(&g_defaultContext);
	if(slected){highlited=true;};
	
	u32 th=GetDefaultFont().linegap;
	
	float _s = *s>=0.0f?*s<=1.0f?*s:1.0f:0.0f;//very indrstundabel , cheks if 0.0 <= *s <= 1.0, if it isnt, set to eather 1.0 or 0.0
	DrawRoundedRectangel(x+10, y+2, w-20, 6, 3, 30, {50,50,60,255}); //the slider
	if(slected){
		DrawEmptyCircle(x+_s*(w-20)+10, y+5, 10,1, 30,  g_defaultHoverColour);
	}

	if(Hover(x, y, w, 20)){
		DrawCircle(x+_s*(w-20)+10, y+5, 10, 30,  g_defaultHoverColour);
		preased|=2;
	}else 	
	if(Clicked(x, y, w, 20) || (slected && GetMouseClickes()&(1<<3)) /*aka, not realeased*/){
		DrawCircle(x+_s*(w-20)+10, y+5, 10, 30,  g_defaultSlecetColour);
		int offset = (int)GetMousePos().x - (int)(x+10);
		offset=offset>(int)(w-20)?(int)(w-20): offset<=0?0:offset;
		*s = ((float)(offset)/ (float)(w-20));
		preased|=1;
		
	}else {
		DrawCircle(x+_s*(w-20)+10, y+5, 10, 30,  g_defaultBackgroundColour);
		if(slected){
			DiscardSelect(&g_defaultContext);
			slected=false;
		}
	}
	
		
	if(preased&1){slected=1;}	

	if(!preased&& GetMouseClickes()&(1<<3) && slected){
	}
	UpdateSelect(slected, highlited, &g_defaultContext);
	

	return preased;
}
