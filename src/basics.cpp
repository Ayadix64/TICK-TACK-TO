#include "indexbuff.h"
#include "shader.h"
#include "utils.h"
#include "batch.hpp"
#include "vertexbuff.h"
#include "vertexarray.h"
#include "shaders.hpp"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <atomic>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../include/tick-tack-to/basics.h"

#define debugy(x) std::cout<<"\n"<<#x<<" : " << x ;


typedef struct {float x,y;u32 c;} Vertex;

#define VERTFG_TRINGELS 0
#define VERTFG_CERCULS  1


typedef struct {
	char Practicul:4;
	bool Enbletextures:1;
	char textureSlot:5;//0x1f = ignore
	int rsv:22;
}__attribute__((packed)) VertexFlags;


TickContext g_defultContext;
std::atomic<bool> g_defultContextIsAlreadySet;




void  GenrateAttribute2DShape(u32 vao, u32 vb, u32 ib){
	CHECK_GL_ERORR(glBindVertexArray(vao));
	CHECK_GL_ERORR(glBindBuffer(GL_ARRAY_BUFFER,vb));
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ib));
	
	CHECK_GL_ERORR(glEnableVertexAttribArray(0));
	CHECK_GL_ERORR(glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(float),0));
	CHECK_GL_ERORR(glEnableVertexAttribArray(1));
	CHECK_GL_ERORR(glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)8));
	CHECK_GL_ERORR(glEnableVertexAttribArray(2));
	CHECK_GL_ERORR(glVertexAttribPointer(2,1,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)12));	
	
	
}




TickContext TickInit(){
	loge("TICK INIT ...");
	std::cout << sizeof(VertexFlags);
	TickContext context;
	context.Shader2D= CreatShader(g_2DShape_vertexshader, g_2DShape_fragmentshader);
	context.uniform2DMvp = GetUniform("u_MVP", context.Shader2D);		
	if(context.uniform2DMvp == -1){
		Eloge("SHADER ERORR");
	}
	context.VAO_2D = GenVertexArray();
	context.VertexBuffer2D = GenVertexBuffer(nullptr, 0);
	context.VertexBuffer2DSize=0;
	context.IndexBuffer2D=GenIndexBuff(nullptr, 0);
	context.IndexBuffer2DSize=0;
		
	GenrateAttribute2DShape(context.VAO_2D, context.VertexBuffer2D, context.IndexBuffer2D);
	context.vertexbatch2DSize=0x1000;
	context.vertexbatchr2D = (float*)malloc(0x1000);
	context.vertexbatch2DPtr=0;

	context.indexbatch2DSize=0x1000;
	context.indexbatchr2D = (u32*)malloc(0x1000);
	context.indexbatch2DPtr=0;
	
	context.window_w=0;
	context.window_h=0;

	if(!g_defultContextIsAlreadySet){
		g_defultContext=context;
		g_defultContextIsAlreadySet=true;
	}
	loge("TICK INIT .");
	return context;
}








void BatcheRendrerAdd(float* vetex , u32 vcount , u32* index, u32 icount , TickContext* context){
	BatchRendringAddIndex(&context->indexbatchr2D, &context->indexbatch2DSize, &context->indexbatch2DPtr, &context->isIndex2DChanged,
		 index, icount, context->vertexbatch2DPtr, 4);
	BatchRendringAddVertex(&context->vertexbatchr2D,&context->vertexbatch2DSize , &context->vertexbatch2DPtr, &context->isVertex2DChanged 
			, vetex, vcount);
	return;
}








void DrawTriangle(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl)
{
	DrawTriangle_ctx(v1,  v2, v3, cl,&g_defultContext);
}



void DrawLine(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl){
	/*float offsetFromeTheSenter = thicknis/2.0f;//we ant the center line to be align with the line that the user want
	if(v1.y == v2.y && v1.x == v2.x){
		return;//wont draw any way lol
	}else if(v1.y==v2.y){
		DrawQuadrilateral({v1.x,v1.y-offsetFromeTheSenter}, {v2.x,v2.y-offsetFromeTheSenter}, {v1.x,v1.y+offsetFromeTheSenter} , {v2.x,v2.y+offsetFromeTheSenter},  cl);
	}else if(v1.x==v2.x){
		DrawQuadrilateral({v1.x-offsetFromeTheSenter,v1.y}, {v2.x-offsetFromeTheSenter,v2.y}, {v1.x+offsetFromeTheSenter,v1.y} , {v2.x+offsetFromeTheSenter,v2.y},  cl);
	}//we wont lose profourmence becuse the user want a renamed rectangel are we?
	else {
		float a = (v1.x-v2.x)/(v2.y-v1.y);//basicly we the  perpendicular line of the line to make a line with in the line
		
		float x_ = sqrtf((offsetFromeTheSenter*offsetFromeTheSenter)/(a*a+1.0)) ;//with some maths, and some deep think, l plk sio ak opopjr ,jdn :kdll k [Segmentation Fult (core dump)]
		float y_ = x_*a ; //the y is bascily f(x);
		DrawQuadrilateral({v1.x-x_,v1.y-y_}, {v2.x-x_,v2.y-y_}, {v1.x+x_,v1.y+y_} , {v2.x+x_,v2.y+y_},  cl);
	}*/
	DrawLine_ctx( v1,  v2,  thicknis,  cl, &g_defultContext);
	return;	
}

void DrawQuadrilateral(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl)// v1___v2
									 //  |   |
									 //  |   |
									 // v3"""v4
{
	
	DrawQuadrilateral_ctx(v1 , v2, v3 , v4,cl,&g_defultContext);
		
}
void DrawRectangel(float x, float y , float w , float h,Vec4c cl){
	DrawQuadrilateral({x,y}, {x+w,y}, {x,y+h}, {x+w,y+h},  cl);
	return;
}


void Draw2DVerteces(Vec2f* verteces , u32 Vertecount , Vec4c cl){
	Draw2DVerteces_ctx(verteces,Vertecount,cl,&g_defultContext);
	return;
}




void Draw2DVerteces(Vec2f* verteces , u32 Vertecount ,u32* indeces,u32 Indexcont, Vec4c cl){
	Draw2DVerteces_ctx(verteces,Vertecount,indeces,Indexcont,cl,&g_defultContext);
	return;
}


void DrawCercel(float x , float y , float r, float steps , Vec4c cl){
	DrawCercel_ctx(x, y, r,  steps,  cl, &g_defultContext);
	return;

}





/************************************* Context Functions **********************************/






void DrawTriangle_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl, TickContext* ctx)
{
	
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false,.textureSlot=0};

	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	float verteces[]{
		v1.x,v1.y,*(float*)&c,*(float*)&flage,
		v2.x,v2.y,*(float*)&c,*(float*)&flage,
		v3.x,v3.y,*(float*)&c,*(float*)&flage
	};
	u32 indece[3]{0,(u32)1,(u32)2};//i know, this is reducled, but i am too lazy to think about a new way to do it with out a index count

	//u32 verty , indexy;
	//g_2DShapesBatchRenderer->Push(verteces,9,indece,3);
	BatcheRendrerAdd(verteces, sizeof(verteces)/sizeof(float), indece, 3, ctx);
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
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false,.textureSlot=0};
	
	u32 indeces[6]{
		0,1,2,
		2,3,1
	};
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;	
	float verteces[]{ 
		v1.x,v1.y,*(float*)&c,*(float*)&flage,
		v2.x,v2.y,*(float*)&c,*(float*)&flage,
		v3.x,v3.y,*(float*)&c,*(float*)&flage,
		v4.x,v4.y,*(float*)&c,*(float*)&flage
	};

	//g_2DShapesBatchRenderer->Push(verteces,sizeof(verteces)/sizeof(float),indeces,sizeof(indeces)/sizeof(u32));
	BatcheRendrerAdd(verteces, sizeof(verteces)/sizeof(float), indeces, sizeof(indeces)/sizeof(u32), ctx);
}
void DrawRectangel_ctx(float x, float y , float w , float h,Vec4c cl,TickContext* ctx){
	DrawQuadrilateral_ctx({x,y}, {x+w,y}, {x,y+h}, {x+w,y+h},  cl,ctx);
	return;
}


void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount , Vec4c cl,TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false,.textureSlot=0};
	

	float* Vertex = (float*)malloc((Vertecount*4)*sizeof(float));
	u32* indeces = (u32*)malloc(Vertecount*4*sizeof(u32));
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	for(u32 i = 0 ; i < Vertecount; i++){
		Vertex[i*4]=verteces[i].x;
		Vertex[i*4+1]=verteces[i].y;
		Vertex[i*4+2]=*(float*)&c;
		Vertex[i*4+3]=*(float*)&flage;
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
	BatcheRendrerAdd(Vertex, Vertecount*4, indeces, Vertecount*3, ctx);
	free(Vertex);
	free(indeces);
	return;
}




void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount ,u32* indeces,u32 Indexcont, Vec4c cl,TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false,.textureSlot=0};


	float* Vertex = (float*)malloc((Vertecount*4)*sizeof(float));
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	for(u32 i = 0 ; i < Vertecount; i++){
		Vertex[i*4]=verteces[i].x;
		Vertex[i*4+1]=verteces[i].y;
		Vertex[i*4+2]=*(float*)&c;
		Vertex[i*4+3]=*(float*)&flage;
	}

	//g_2DShapesBatchRenderer->Push(Vertex,Vertecount*3,indeces,Indexcont);
	BatcheRendrerAdd(Vertex, Vertecount*4, indeces, Indexcont, ctx);
	free(Vertex);
	return;
}


void DrawCercel_ctx(float x , float y , float r, float steps , Vec4c cl, TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_CERCULS,.Enbletextures=false,.textureSlot=0};
	u32 indeces[6]{
		0,1,2,
		2,3,1
	};
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;	
	float verteces[]{ 
		x+r,y+r,*(float*)&c,0,*(float*)&flage,
		x+r,y-r,*(float*)&c,1,*(float*)&flage,
		x-r,y+r,*(float*)&c,2,*(float*)&flage,
		x-r,y-r,*(float*)&c,3,*(float*)&flage
	};

	BatcheRendrerAdd(verteces, sizeof(verteces)/sizeof(float), indeces, sizeof(indeces)/sizeof(u32), ctx);

	return;

}






/************************************** Rendrer ****************************************/




void TickRendre(GLFWwindow* window){
	TickRendre_ctx(window, &g_defultContext);

	return;
}


void TickNewFrame(){
	TickContext* context = &g_defultContext;
	context->indexbatch2DPtr=0;
	context->vertexbatch2DPtr=0;
	context->isVertex2DChanged=false;
	context->isIndex2DChanged=false;
	return;

}





void TickRendre_ctx(GLFWwindow* window,TickContext* ctx){
	TickContext& context = *ctx;
	
	if(!g_defultContextIsAlreadySet){
		Eloge("Rendring without a Context ===> did you call TickInit() ?");
		return;
	}
	
	CHECK_GL_ERORR(glUseProgram(ctx->Shader2D));
	
	//if the window changed, update the mvp
	int window_w=0, window_h=0;
	glfwGetFramebufferSize(window, &window_w, &window_h);
	if(window_w!=context.window_w || window_h!=context.window_h){
		glm::mat4 proj = glm::ortho(0.0f,(float)window_w,(float)window_h,0.0f,-1.0f,1.0f);
		glViewport(0,0,window_w,window_h);	
		glUniformMatrix4fv(context.uniform2DMvp,1,GL_FALSE,&proj[0][0]);
		context.window_w=window_w;
		context.window_h=window_h;
	}

	bool isitChanged = true;
	static int points=0; 
	
	if(context.isVertex2DChanged){
		if(context.vertexbatch2DPtr*sizeof(float)>context.VertexBuffer2DSize){
			RegenrateVertexBuffer(&context.VertexBuffer2D,context.vertexbatchr2D,context.vertexbatch2DPtr*4);
			context.VertexBuffer2DSize=context.vertexbatch2DPtr*sizeof(float);
			std::cout<<"\nRegnarate Vertex Buffer to " << context.VertexBuffer2DSize;
		isitChanged=true;
		}else {
			glBindBuffer(GL_ARRAY_BUFFER,context.VertexBuffer2D);
			glBufferSubData(GL_ARRAY_BUFFER,0,context.vertexbatch2DPtr*4,context.vertexbatchr2D);
			//FullVertexBuffer(context.vertexbatchr2D, context.vertexbatch2DPtr*4);
		}
	}
	if(context.isIndex2DChanged){
		if(context.indexbatch2DPtr*sizeof(u32)>context.IndexBuffer2DSize){
			RegenrateIndexBuffer(&context.IndexBuffer2D,context.indexbatchr2D,context.indexbatch2DPtr*4);

			context.IndexBuffer2DSize=context.indexbatch2DPtr*sizeof(u32);
			std::cout<<"\nRegnarate Index Buffer to " << context.IndexBuffer2DSize;
			isitChanged=true;
		}else {
			CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,context.IndexBuffer2D));
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,context.indexbatch2DPtr*4,context.indexbatchr2D);
			
		}
	}
	if(isitChanged){
		RegenrateVetexArray(&context.VAO_2D);
		GenrateAttribute2DShape(context.VAO_2D, context.VertexBuffer2D, context.IndexBuffer2D);
	}
	
	

	CHECK_GL_ERORR(glBindVertexArray(context.VAO_2D));
	CHECK_GL_ERORR(glBindBuffer(GL_ARRAY_BUFFER,context.VertexBuffer2D));
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,context.IndexBuffer2D));
	
	CHECK_GL_ERORR(glDrawElements(GL_TRIANGLES, context.indexbatch2DPtr, GL_UNSIGNED_INT, nullptr));

	return;
}
void TickNewFrame_ctx(TickContext* context){
	context->indexbatch2DPtr=0;
	context->vertexbatch2DPtr=0;
	context->isVertex2DChanged=false;
	context->isIndex2DChanged=false;
	return;
}


void TickClose(){
	if(g_defultContextIsAlreadySet){
		free(g_defultContext.indexbatchr2D);
		free(g_defultContext.vertexbatchr2D);
		g_defultContextIsAlreadySet=false;
	}else {
		Eloge("Tick never init to close");
	}
}


void TickClose_ctx(TickContext* context){
	if(!memcmp(context,&g_defultContext,sizeof(TickContext))){
		TickClose();
		return;
	}else{
		free(context->indexbatchr2D);
		free(context->vertexbatchr2D);
	}
}
