#include "core.h"
#include "utils.h"
#include "shaders.h"
#include "render.h"

#include <GL/gl.h>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <atomic>
#include <string>
#include <strings.h>

#include "externel/stb_image.h"
#include "../include/tick-tack-to/basics.h"

#define debugy(x) std::cout<<#x<<" : " << x<<"\n" ;


typedef struct {float x,y;u32 c;} Vertex;

#define VERTFG_TRINGELS 0
#define VERTFG_CERCULS  1


typedef struct {
	char Practicul:4;
	bool Enbletextures:1;
	int rsv:27;
}__attribute__((packed)) VertexFlags;


TickContext g_defaultContext;
std::atomic<bool> g_defaultContextIsAlreadySet=false;
std::atomic<bool> g_defaultFontAlreadySet=false; 
void initDefautlFont();
void InitUI();

TickContext TickInit(){
	TickContext context;
	if(g_defaultContextIsAlreadySet){
		context.Shader2D = g_defaultContext.Shader2D;
	}else {
		context.Shader2D= CreatShader(g_2DShape_vertexshader, g_2DShape_fragmentshader);
	}
	context.uniform2DMvp = GetUniform("u_MVP", context.Shader2D);		

	if(context.uniform2DMvp == -1){
		Eloge("SHADER ERORR");
	}
	InitlizeRendrer(&context.Shape2D);
	Genrate2DShapeAttribute(context.Shape2D.VAO, context.Shape2D.VertexBuffer, context.Shape2D.IndexBuffer);
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (int*)&context.maxTexturesSlotsSepurted);//geting the maximum texture slots per texture
	if(context.maxTexturesSlotsSepurted > TICK_MAX_TEXTURE_SLOTS_SEPURTED){ 
		context.maxTexturesSlotsSepurted=TICK_MAX_TEXTURE_SLOTS_SEPURTED;
			Wloge("The maximum Textures slots sepurted ny your GPU is more than what TICK-TACK-TO can handel, so it will use "
			       +std::to_string(TICK_MAX_TEXTURE_SLOTS_SEPURTED)+" slots");
	}

	debugy(context.maxTexturesSlotsSepurted);
	
	context.samplerCount=0;
	context.samplerPtr=0;
	
	context.window_w=0;
	context.window_h=0;
	context.scaleX=1.0f;
	context.scaleY=1.0f;
	context.Z = TICK_TOP_Z;	


	if(!g_defaultContextIsAlreadySet){
		g_defaultContext=context;
		g_defaultContextIsAlreadySet=true;
	}
	if(!g_defaultFontAlreadySet){
		initDefautlFont();
		InitUI();		
		g_defaultFontAlreadySet=true;
	}
	glUseProgram(context.Shader2D);
	for(int i = 0 ; i < MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB && i < context.maxTexturesSlotsSepurted; i++){
		char textureN[50];
		sprintf(textureN,"texture%d",i);
		u32 text =GetUniform((const char*)textureN, context.Shader2D);
		if(text!=-1){
			glUniform1i(text,i);
		}
		//goood bruh in her
	}
	glEnable(GL_DEPTH_TEST);
glDepthMask(GL_TRUE);
glDepthFunc(GL_LEQUAL);
glDepthRange(0.0f, 1.0f);
glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
glEnable(GL_SAMPLE_ALPHA_TO_ONE);
glEnable(GL_BLEND);
glBlendEquation(GL_FUNC_ADD);
glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_ALPHA_TEST);
glAlphaFunc(GL_GREATER, 0.1f);

glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	/*glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glDepthFunc(GL_LESS);
	*/

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
   	// glDepthFunc(GL_LEQUAL);

	return context;
}

TickContext* GetDefaultContext(){return &g_defaultContext;}

void SetScaleX(float scale){
	SetScaleX_ctx(&g_defaultContext, scale);
}
void SetScaleY(float scale){
	SetScaleY_ctx(&g_defaultContext, scale);
}
void SetScaleXY( float scalex, float scaley){
	SetScaleXY_ctx(&g_defaultContext, scalex, scaley);
}
void SetScale(float scale){
	SetScale_ctx(&g_defaultContext, scale);
}



void SetScaleX_ctx(TickContext* ctx, float scale){
	ctx->scaleX=scale;
}

void SetScaleY_ctx(TickContext* ctx, float scale){
	ctx->scaleY=scale;
}

void SetScaleXY_ctx(TickContext* ctx, float scalex, float scaley){
	ctx->scaleX=scalex;
	ctx->scaleY=scaley;
}
void SetScale_ctx(TickContext* ctx, float scale){
	ctx->scaleX=scale;
	ctx->scaleY=scale;
}







void DrawTriangle(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl)
{
	DrawTriangle_ctx(v1,  v2, v3, cl,&g_defaultContext);
}



void DrawLine(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl){

	DrawLine_ctx( v1,  v2,  thicknis,  cl, &g_defaultContext);
	return;	
}

void DrawQuadrilateral(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl)// v1___v2
									 //  |   |
									 //  |   |
									 // v3"""v4
{
	
	DrawQuadrilateral_ctx(v1 , v2, v3 , v4,cl,&g_defaultContext);
		
}
void DrawRectangel(float x, float y , float w , float h,Vec4c cl){
	DrawQuadrilateral({x,y}, {x+w,y}, {x,y+h}, {x+w,y+h},  cl);
	return;
}


void Draw2DVerteces(Vec2f* verteces , u32 Vertecount , Vec4c cl){
	Draw2DVerteces_ctx(verteces,Vertecount,cl,&g_defaultContext);
	return;
}




void Draw2DVerteces(Vec2f* verteces , u32 Vertecount ,u32* indeces,u32 Indexcont, Vec4c cl){
	Draw2DVerteces_ctx(verteces,Vertecount,indeces,Indexcont,cl,&g_defaultContext);
	return;
}


void DrawCircle(float x , float y , float r, float steps , Vec4c cl){
	DrawCircle_ctx(x, y, r,  steps,  cl, &g_defaultContext);
	return;

}
void DrawCircleSegment(float x , float y , float r, float segmetDegree , float segmentsDegreeStart, float segments , Vec4c cl)
/*	startDegree (0° on this case)
 *      __
 *      | ^,   the segmentDgree(90° in this case)
 *     r|   \
 *     y|___|
 * 	x
 * hope that this is straid forwared*/
{

	DrawCircleSegment_ctx(x, y, r, segmetDegree, segmentsDegreeStart, segments, cl, &g_defaultContext);
}
void DrawRoundedRectangel(float x, float y , float w , float h,float r , float segments ,Vec4c cl){
	DrawRoundedRectangel_ctx(x, y, w, h, r, segments, cl, &g_defaultContext);

}








/************************************* Context Functions **********************************/






void DrawTriangle_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl, TickContext* ctx)
{
	
	ctx->Z-=TICK_Z_OFSSET;
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false};

	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	float verteces[]{
		v1.x,v1.y,ctx->Z,*(float*)&c,*(float*)&flage,0,0,0,
		v2.x,v2.y,ctx->Z,*(float*)&c,*(float*)&flage,0,0,0,
		v3.x,v3.y,ctx->Z,*(float*)&c,*(float*)&flage,0,0,0
	};
	u32 indece[3]{0,(u32)1,(u32)2};//i know, this is reducled, but i am too lazy to think about a new way to do it with out a index count

	//u32 verty , indexy;
	//g_2DShapesBatchRen	derer->Push(verteces,9,indece,3);
	BatcheRendrerAdd2DShape(verteces, sizeof(verteces)/sizeof(float), indece, 3,8, &ctx->Shape2D);
	
	
}



void DrawLine_ctx(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl,TickContext* ctx){
	float offsetFromeTheSenter = thicknis/2.0f;//we ant the center line to be align with the line that the user want
	if(v1.y == v2.y && v1.x == v2.x){
		return;//wont draw any way lol
	}else if(v1.y==v2.y){
		DrawQuadrilateral_ctx({v1.x,v1.y-offsetFromeTheSenter}, {v2.x,v2.y-offsetFromeTheSenter}, {v1.x,v1.y+offsetFromeTheSenter} , {v2.x,v2.y+offsetFromeTheSenter},  cl,ctx);
	}else if(v1.x==v2.x){
		DrawQuadrilateral_ctx({v1.x-offsetFromeTheSenter,v1.y}, {v2.x-offsetFromeTheSenter,v2.y}, {v1.x+offsetFromeTheSenter,v1.y} , {v2.x+offsetFromeTheSenter,v2.y},  cl,ctx);
	}//we wont lose profourmence becuse the user want a renamed rectangel are we?
	else {
		float a = (v1.x-v2.x)/(v2.y-v1.y);//basicly we the  perpendicular line of the line to make a line with in the line
		
		float x_ = sqrtf((offsetFromeTheSenter*offsetFromeTheSenter)/(a*a+1.0)) ;//with some maths, and some deep think, l plk sio ak opopjr ,jdn :kdll k [Segmentation Fult (core dump)]
		float y_ = x_*a ; //the y is bascily f(x);
		DrawQuadrilateral_ctx({v1.x-x_,v1.y-y_}, {v2.x-x_,v2.y-y_}, {v1.x+x_,v1.y+y_} , {v2.x+x_,v2.y+y_},  cl,ctx);
	}
	
	return;	
}

void DrawQuadrilateral_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl, TickContext* ctx)
{
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false};
	
	ctx->Z-=TICK_Z_OFSSET;
	u32 indeces[6]{
		0,1,2,
		2,3,1
	};
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;	
	float verteces[]{ 
		v1.x,v1.y,ctx->Z,*(float*)&c,*(float*)&flage,0,0,0,
		v2.x,v2.y,ctx->Z,*(float*)&c,*(float*)&flage,0,0,0,
		v3.x,v3.y,ctx->Z,*(float*)&c,*(float*)&flage,0,0,0,
		v4.x,v4.y,ctx->Z,*(float*)&c,*(float*)&flage,0,0,0
	};

	//g_2DShapesBatchRenderer->Push(verteces,sizeof(verteces)/sizeof(float),indeces,sizeof(indeces)/sizeof(u32));
	BatcheRendrerAdd2DShape(verteces, sizeof(verteces)/sizeof(float), indeces, sizeof(indeces)/sizeof(u32),8, &ctx->Shape2D);
	
}
void DrawRectangel_ctx(float x, float y , float w , float h,Vec4c cl,TickContext* ctx){
	DrawQuadrilateral_ctx({x,y}, {x+w,y}, {x,y+h}, {x+w,y+h},  cl,ctx);
	return;
}



void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount , Vec4c cl,TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false};
	
	ctx->Z-=TICK_Z_OFSSET;

	float* Vertex = (float*)malloc((Vertecount*8)*sizeof(float));
	u32* indeces = (u32*)malloc(Vertecount*3*sizeof(u32));
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	for(u32 i = 0 ; i < Vertecount; i++){
		Vertex[i*8]=verteces[i].x;
		Vertex[i*8+1]=verteces[i].y;
		Vertex[i*8+2]=ctx->Z;
		Vertex[i*8+3]=*(float*)&c;
		Vertex[i*8+4]=*(float*)&flage;
		Vertex[i*8+5]=0;
		Vertex[i*8+6]=0;
		Vertex[i*8+7]=0;
	}
	for(u32 i = 0 ; i < Vertecount ; i++){
		indeces[i*3] = i;
		if(Vertecount-i == 2){
			indeces[i*3+1] = i+1;
			indeces[i*3+2] = 0;

		}
		else if(Vertecount-i == 1){
			indeces[i*3+1] = 0;
			indeces[i*3+2] = 1;

		}else{ 
			indeces[i*3+1] = i+1;
			indeces[i*3+2] = i+2;
		}
	}
	//g_2DShapesBatchRenderer->Push(Vertex,Vertecount*3,indeces,Vertecount*3);
	BatcheRendrerAdd2DShape(Vertex, Vertecount*8, indeces, Vertecount*3,8, &ctx->Shape2D);
	
	free(Vertex);
	free(indeces);
	return;
}




void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount ,u32* indeces,u32 Indexcont, Vec4c cl,TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false};
	
	ctx->Z-=TICK_Z_OFSSET;

	float* Vertex = (float*)malloc((Vertecount*8)*sizeof(float));
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	for(u32 i = 0 ; i < Vertecount; i++){
		Vertex[i*8]=verteces[i].x;
		Vertex[i*8+1]=verteces[i].y;
		Vertex[i*8+2]=ctx->Z;
		Vertex[i*8+3]=*(float*)&c;
		Vertex[i*8+4]=*(float*)&flage;
		Vertex[i*8+5]=0;
		Vertex[i*8+6]=0;
		Vertex[i*8+7]=0;
	}

	BatcheRendrerAdd2DShape(Vertex, Vertecount*8, indeces, Indexcont, 8,&ctx->Shape2D);
	free(Vertex);

	
	return;
}


void DrawCircle_ctx(float x , float y , float r, float steps , Vec4c cl, TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_CERCULS,.Enbletextures=false};
	
	ctx->Z-=TICK_Z_OFSSET;
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;	
	
	float verteces[24]{x,y  ,ctx->Z,*(float*)&c,*(float*)&flage,x,y,0.0f,
		 	   x,y-r,ctx->Z,*(float*)&c,*(float*)&flage,x,y,0.0f,
			   x,y-r,ctx->Z,*(float*)&c,*(float*)&flage,x,y,360.0f/steps};
	u32 indeces[3]{0,1,2};
	BatcheRendrerAdd2DShape(verteces, 24, indeces, 3,8, &ctx->Shape2D);
	
	for(int i = 1; i < steps ; i++){
		verteces[0] = x;
		verteces[1] = y-r;
		verteces[2] = ctx->Z;
		verteces[3] = *(float*)&c;
		verteces[4] = *(float*)&flage;
		verteces[5] = x;
		verteces[6] = y;
		float offset = ((float)(i+1))*(360.0f/(steps));
		verteces[7] =  offset>360.0f?360.0f:offset;
		indeces[0]=-i-2;
		indeces[1]=-1;
		indeces[2]=0;
		BatcheRendrerAdd2DShape(verteces, 8, indeces, 3,8,&ctx->Shape2D);
	}
	
	// now this is kinde good
	return;

}






void DrawCircleSegment_ctx(float x , float y , float r, float segmetDegree , float segmentsDegreeStart, float segments , Vec4c cl, TickContext* ctx){
/*	startDegree (0° on this case)
 *      __
 *      | ^,   the segmentDgree(90° in this case)
 *     r|   \
 *     y|___|
 * 	x
 * hope that this is straid forwared*/

	VertexFlags flage{.Practicul=VERTFG_CERCULS,.Enbletextures=false};
	
	ctx->Z-=TICK_Z_OFSSET;
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;	
	
	float verteces[24]{x,y  ,ctx->Z,*(float*)&c,*(float*)&flage,x,y,0.0f,
		 	   x,y-r,ctx->Z,*(float*)&c,*(float*)&flage,x,y,segmentsDegreeStart,
			   x,y-r,ctx->Z,*(float*)&c,*(float*)&flage,x,y,segmetDegree/segments+segmentsDegreeStart};
	u32 indeces[3]{0,1,2};
	BatcheRendrerAdd2DShape(verteces, 24, indeces, 3,8, &ctx->Shape2D);
	
	for(int i = 1; i < segments ; i++){
		verteces[0] = x;
		verteces[1] = y-r;
		verteces[2] = ctx->Z;
		verteces[3] = *(float*)&c;
		verteces[4] = *(float*)&flage;
		verteces[5] = x;
		verteces[6] = y;
		float offset = ((float)(i+1))*(segmetDegree/(segments));
		verteces[7] =  (offset>segmetDegree?segmetDegree:offset)+segmentsDegreeStart;
		indeces[0]=-i-2;
		indeces[1]=-1;
		indeces[2]=0;
		BatcheRendrerAdd2DShape(verteces, 8, indeces, 3,8,&ctx->Shape2D);
	}
	
	// now this is kinde good
	return;

}

void DrawRoundedRectangel_ctx(float x, float y , float w , float h,float r , float segments ,Vec4c cl,TickContext* ctx){
	if(!r){
		DrawQuadrilateral_ctx({x,y}, {x+w,y}, {x,y+h}, {x+w,y+h},  cl,ctx);
		return;
	}
	DrawRectangel_ctx(x, y+r, r, h-r*2, cl,ctx);
	DrawRectangel_ctx(x+w-r, y+r, r, h-r*2, cl,ctx);
	DrawRectangel_ctx(x+r, y, w-r*2, h, cl,ctx);
	
	DrawCircleSegment_ctx(x+r  , y+r  , r, 90.0f, 270.0f, segments, cl, ctx);
	DrawCircleSegment_ctx(x+w-r, y+r  , r, 90.0f, 0.0f  , segments, cl, ctx);
	DrawCircleSegment_ctx(x+r  , y+h-r, r, 90.0f, 180.0f, segments, cl, ctx);
	DrawCircleSegment_ctx(x+w-r, y+h-r, r, 90.0f, 90.0f , segments, cl, ctx);
	return;
}


/************************************** Textures ***************************************/







TickTexture2D LoadTexture(void* bitmap,float w, float h, u32 bpp){
	return LoadTexture_ctx(bitmap,w, h, bpp, &g_defaultContext);
}
TickTexture2D LoadTextureFromeFile(const char * fileName){
	return LoadTextureFromeFile_ctx(fileName, &g_defaultContext);
}
void DrawTexture(TickTexture2D index,float x , float y , float w,  float h ){
	DrawTexture_ctx(index, x, y, w,  h, &g_defaultContext);
	return;
}
void DrawTextureSegment(TickTexture2D texture,float x , float y  , float w, float h ,float xx , float yy ,  float ww,  float hh ){
	return DrawTextureSegment_ctx(texture, x, y,  w,  h, xx, yy,  ww,  hh, &g_defaultContext);//heh, did you know that you can do that?
}
void DrawTextureSegmentExtended(TickTexture2D texture,Vec2f v1 , Vec2f v2  , Vec2f v3, Vec2f v4, Vec2f tc1 , Vec2f tc2 , Vec2f tc3 , Vec2f tc4 ){
	return DrawTextureSegmentExtended_ctx(texture,v1, v2, v3, v4,tc1,tc2,tc3,tc4, &g_defaultContext);
}



void RemoveTexture(TickTexture2D* index){
	RemoveTexture_ctx(index, &g_defaultContext);
	return;
}

void ReloadTextureFromeFile(TickTexture2D* index, const char* fileName){
	ReloadTextureFromeFile_ctx(index, fileName, &g_defaultContext);
	return;
}

void ReloadTexture(TickTexture2D* index, void* data,u32 w , u32 h , u32 bpp ){
	ReloadTexture_ctx(index, data, w, h, bpp, &g_defaultContext);
	return;
}







void DrawTexture_ctx(TickTexture2D texture,float x , float y , float w,  float h , TickContext* ctx){
	
	ctx->Z-=TICK_Z_OFSSET;
	int sampler = texture.index/ctx->maxTexturesSlotsSepurted;
	int slot = texture.index%ctx->maxTexturesSlotsSepurted;
	if(texture.index==-1 || 
	  sampler >= ctx->samplerPtr ||
	  !(ctx->samplers[sampler].texture[slot])){
		Eloge("Unvaliad Texture");
		return;
	}
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=true};
	u32 indeces[6]{
		0,1,2,
		2,3,1
	};
	float verteces[]{ 
		x,y    ,ctx->Z ,*(float*)&slot,*(float*)&flage,0.0f,0.0f, 
		x,y+h  ,ctx->Z ,*(float*)&slot,*(float*)&flage,0.0f,1.0f, 
		x+w,y  ,ctx->Z ,*(float*)&slot,*(float*)&flage,1.0f,0.0f,
		x+w,y+h,ctx->Z ,*(float*)&slot,*(float*)&flage,1.0f,1.0f 
	};
	BatcheRendrerAdd2DShape(verteces, sizeof(verteces)/sizeof(float), indeces, sizeof(indeces)/sizeof(u32),7,&ctx->samplers[sampler].rendrer);
	
}





void DrawTextureSegment_ctx(TickTexture2D texture,float x , float y  , float w, float h ,float xx , float yy ,  float ww,  float hh , TickContext* ctx){
	DrawTextureSegmentExtended_ctx(texture, {x,y}, {x+w,y},{x,y+h}, {x+w,y+h}, {xx,yy}, {xx+ww,yy}, {xx,yy+hh}, {xx+ww,yy+hh}, ctx);		
}



void DrawTextureSegmentExtended_ctx(TickTexture2D texture,Vec2f v1 , Vec2f v2  , Vec2f v3, Vec2f v4 , 
		                    Vec2f tc1 , Vec2f tc2 , Vec2f tc3 , Vec2f tc4 , TickContext* ctx)

{
	ctx->Z-=TICK_Z_OFSSET;
	int sampler = texture.index/ctx->maxTexturesSlotsSepurted;
	int slot = texture.index%ctx->maxTexturesSlotsSepurted;
	if(texture.index==-1 || 
	  sampler >= ctx->samplerPtr ||
	  !(ctx->samplers[sampler].texture[slot])){
		Eloge("Unvaliad Texture");
		return;
	}
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=true};
	u32 indeces[6]{
		0,1,2,
		2,3,1
	};
	Vec2f segmentveteces[4]= {{tc1.x/(float)texture.w,tc1.y/(float)texture.h},
				  {tc2.x/(float)texture.w,tc2.y/(float)texture.h},
				  {tc3.x/(float)texture.w,tc3.y/(float)texture.h},
				  {tc4.x/(float)texture.w,tc4.y/(float)texture.h}};
	float verteces[]{ 
		v1.x,v1.y,ctx->Z ,*(float*)&slot,*(float*)&flage,segmentveteces[0].x,segmentveteces[0].y, 
		v2.x,v2.y,ctx->Z ,*(float*)&slot,*(float*)&flage,segmentveteces[1].x,segmentveteces[1].y, 
		v3.x,v3.y,ctx->Z ,*(float*)&slot,*(float*)&flage,segmentveteces[2].x,segmentveteces[2].y,
		v4.x,v4.y,ctx->Z ,*(float*)&slot,*(float*)&flage,segmentveteces[3].x,segmentveteces[3].y, 
	};//textures are weard, they are truely are
	BatcheRendrerAdd2DShape(verteces, sizeof(verteces)/sizeof(float),indeces, sizeof(indeces)/sizeof(u32),7,&ctx->samplers[sampler].rendrer);
	
	
}







TickTexture2D LoadTexture_ctx(void* bitmap,float w, float h, u32 bpp, TickContext* ctx){
	TickTexture2D ret;
	u32 samplerNumber = -1;
	u32 textureSlot=-1;
	u32 notempty = false;

	for(int i = 0 ; i < ctx->samplerPtr ; i++){
		notempty=false;
		for(int ii = 0 ; ii < ctx->maxTexturesSlotsSepurted ; ii++){
			notempty|=ctx->samplers[i].texture[ii];
			if(!ctx->samplers[i].texture[ii] && samplerNumber==-1 && textureSlot==-1){
				textureSlot=ii;
				samplerNumber=i;
				
			}

		}
		if(samplerNumber!=-1){break;}
	}
		

	if(samplerNumber==-1){
		if(ctx->samplerCount<=ctx->samplerPtr+1){
			ctx->samplerCount+=50;
			ctx->samplers=(TickTextureRendrerStruct*)realloc(ctx->samplers, ctx->samplerCount*sizeof(TickTextureRendrerStruct));
			
		}
		samplerNumber=ctx->samplerPtr;
		textureSlot=0;
		memset(ctx->samplers[samplerNumber].texture,0,sizeof(ctx->samplers[samplerNumber].texture));
		InitlizeRendrer(&ctx->samplers[samplerNumber].rendrer);
		ctx->samplerPtr++;
		notempty=true;
	}

	ctx->samplers[samplerNumber].texture[textureSlot] = GenTexture();
	CHECK_GL_ERORR(glBindTexture(GL_TEXTURE_2D, ctx->samplers[samplerNumber].texture[textureSlot]));
	SetTextureData((u8*)bitmap, w, h, bpp);

	if(!notempty){
		InitlizeRendrer(&ctx->samplers[samplerNumber].rendrer);
	}
	ret.index=samplerNumber*ctx->maxTexturesSlotsSepurted + textureSlot;
	ret={.index=samplerNumber*ctx->maxTexturesSlotsSepurted + textureSlot,
	     .w=(u32)w,.h=(u32)h,.bpp=bpp};
	return ret;//samplerNumber*ctx->maxTexturesSlotsSepurted + textureSlot;
}




TickTexture2D LoadTextureFromeFile_ctx(const char * fileName, TickContext *ctx){
	int w,h,bpp;
	TickTexture2D ret{.index=(u32)-1};
	u8* pb = stbi_load((const char*)fileName, (int*)&w, (int*)&h, (int*)&bpp, (int)4);
	if(!pb){
		Eloge("Cant Load "+ std::string(fileName)+" , "+std::string(stbi_failure_reason()));
		return ret;
	}	

	ret = LoadTexture_ctx(pb, w,h,  4, ctx);	
	stbi_image_free(pb);
	
	return ret;
}








void ReloadTexture_ctx(TickTexture2D* texture, void* data,u32 w , u32 h , u32 bpp , TickContext* ctx){
	int sampler = texture->index/ctx->maxTexturesSlotsSepurted;
	int slot = texture->index%ctx->maxTexturesSlotsSepurted;
	if(texture->index==-1 || 
	   sampler >= ctx->samplerPtr ||
	  !(ctx->samplers[sampler].texture[slot])){
		Eloge("Unvaliad Texture");
		return;
	}
	
	CHECK_GL_ERORR(glBindTexture(GL_TEXTURE_2D, ctx->samplers[sampler].texture[slot]));
	SetTextureData((u8*)data, w, h, bpp);
	texture->w=w;
	texture->h=h;
	texture->bpp=bpp;
	return;
}



void ReloadTextureFromeFile_ctx(TickTexture2D* texture, const char* fileName, TickContext* ctx){
	int sampler = texture->index/ctx->maxTexturesSlotsSepurted;
	
	u32 textureSlot = texture->index%ctx->maxTexturesSlotsSepurted;
	if(texture->index==-1 || 
	  sampler >= ctx->samplerPtr ||
	  !ctx->samplers[sampler].texture[textureSlot]){
		Eloge("Unvaliad Texture");
		return;
	}

	int w,h,bpp;
	u8* pb = stbi_load((const char*)fileName, (int*)&w, (int*)&h, (int*)&bpp, (int)4);
	if(!pb){
		Eloge("Cant Load "+ std::string(fileName)+" , "+std::string(stbi_failure_reason()));
		return;
	}
	ReloadTexture_ctx(texture, pb,  w, h, 4, ctx);
	return;
}



void RemoveTexture_ctx(TickTexture2D* texture, TickContext* ctx){
	int sampler = texture->index/ctx->maxTexturesSlotsSepurted;
	
	u32 slot = texture->index%ctx->maxTexturesSlotsSepurted;
	if(texture->index==-1 || 
	  sampler >= ctx->samplerPtr ||
	  !ctx->samplers[sampler].texture[slot]){
		Eloge("Unvaliad Texture");
		return;
	}
	

	CHECK_GL_ERORR(glDeleteTextures(1, &ctx->samplers[sampler].texture[slot]));
	ctx->samplers[sampler].texture[slot]=0;

	u32 notempty = false;
	for(int i = 0 ; i < sizeof(ctx->samplers[sampler].texture) / sizeof(u32);++i){
		notempty|=ctx->samplers[sampler].texture[i]; 
		if(notempty)break;
	};
	

	if(!notempty){
		DeletRendrer(&ctx->samplers[sampler].rendrer);
	}
	*texture={(u32)-1,(u32)-1,(u32)-1,(u32)-1};
	//we cant reorginaze them becuse we have to reindex all of them, at the same time we cant 
	//return a texture object becuse we want to use all the avliable slots for max profourmence
	//it is a traide of betwen gpu profourmence and tiny system memory
	//TODO: my be beter layout?
	return;
}







/************************************** Rendrer  ****************************************/







void TickRendre(GLFWwindow* window){
	TickRendre_ctx(window, &g_defaultContext);

	return;
}


void TickNewFrame(){
	TickNewFrame_ctx(&g_defaultContext);
	return;

}


void TickRendre_ctx(GLFWwindow* window,TickContext* ctx){
	TickContext& context = *ctx;
	if(ctx->Z<=TICK_BUTTOM_Z){
		Eloge("Z <=  "+std::to_string(TICK_BUTTOM_Z)+" you draw too much and part of that will not been rendred!");
	}
	
	if(!g_defaultContextIsAlreadySet){
		Eloge("Rendring without a Context ===> did you call TickInit() ?");
		return;
	}
	
	int usedShader ;
	//glGetIntegerv(GL_ACTIVE_PROGRAM,&usedShader);
	if(usedShader!=ctx->Shader2D){
		CHECK_GL_ERORR(glUseProgram(ctx->Shader2D));
	}
	
	//if the window changed, update the mvp
	int real_w=0, real_h=0;
	glfwGetFramebufferSize(window, &real_w, &real_h);
	int window_w= (int)(((float)real_w)/context.scaleX);
	int window_h= (int)(((float)real_h)/context.scaleY);
	static float iw = 0.0;
	if(window_w!=context.window_w || window_h!=context.window_h){
		float proj[4][4] ;
		for(int i= 0 ; i < 16; i++){
			proj[i/4][i%4]=0.0f;
			
		}
		proj[0][0] = 2.0f / (float)window_w;
		proj[1][1] =-2.0f / (float)window_h;
		proj[2][2] = 1.0f;
		proj[3][0] =-1.0f;
		proj[3][1] = 1.0f;
		proj[3][3] = 1.0f;


		glViewport(0,0,real_w,real_h);
		glUniformMatrix4fv(context.uniform2DMvp,1,GL_FALSE,&proj[0][0]);
		context.window_w=window_w;
		context.window_h=window_h;
	}
	Render(&context.Shape2D);
	for(int i = 0 ; i < context.samplerPtr ; i++){
		//printf("\n**************** texture %d ***********************\n",i);
		RenderTexture(&context.samplers[i]);
	}


	return;
}
void TickNewFrame_ctx(TickContext* context){
	ResetRendrer(&context->Shape2D);
	ResetRendrer(&context->ShapeCir2D);
	for(int i = 0 ; i < context->samplerPtr ; i++){
		ResetRendrer(&context->samplers[i].rendrer);
	}

	context->Z=TICK_TOP_Z;
	return;
}


void TickClose(){
	if(!g_defaultContextIsAlreadySet){
		Eloge("Tick never init to close");
		return;
	}
	g_defaultContextIsAlreadySet=false;

}


void TickClose_ctx(TickContext* context){

	DeletRendrer(&context->Shape2D);	
	DeletRendrer(&context->ShapeCir2D);
}
