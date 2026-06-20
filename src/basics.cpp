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

void  GenrateAttribute2DCirShape(u32 vao, u32 vb, u32 ib){ // yeah, circuls are a defrunt kinde of shape, how about that?
	CHECK_GL_ERORR(glBindVertexArray(vao));
	CHECK_GL_ERORR(glBindBuffer(GL_ARRAY_BUFFER,vb));
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ib));
	
	CHECK_GL_ERORR(glEnableVertexAttribArray(0));
	CHECK_GL_ERORR(glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,7*sizeof(float),0));
	CHECK_GL_ERORR(glEnableVertexAttribArray(1));
	CHECK_GL_ERORR(glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)8));
	CHECK_GL_ERORR(glEnableVertexAttribArray(2));
	CHECK_GL_ERORR(glVertexAttribPointer(2,1,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)12));	
	CHECK_GL_ERORR(glEnableVertexAttribArray(3));
	CHECK_GL_ERORR(glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)16));	
	
}

void InitlizeRendrer(TickRendrerStruct* rendrer){
	rendrer->VAO = GenVertexArray();
	rendrer->VertexBuffer=GenVertexBuffer(NULL, 0);
	rendrer->IndexBuffer =GenIndexBuff(NULL, 0 );
	rendrer->VertexBufferSize=0;
	rendrer->IndexBufferSize=0;

	rendrer->vertexbatchSize=0x1000;
	rendrer->vertexbatchPtr=0;
	rendrer->vertexbatchr=(float*)malloc(0x1000);
	
	rendrer->indexbatchSize=0x1000;
	rendrer->indexbatchPtr=0;
	rendrer->indexbatchr=(u32*)malloc(0x1000);
	return;
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
	InitlizeRendrer(&context.Shape2D);	
	InitlizeRendrer(&context.ShapeCir2D);
	GenrateAttribute2DShape(context.Shape2D.VAO, context.Shape2D.VertexBuffer, context.Shape2D.IndexBuffer);
	GenrateAttribute2DCirShape(context.ShapeCir2D.VAO, context.ShapeCir2D.VertexBuffer, context.ShapeCir2D.IndexBuffer);

	
	context.window_w=0;
	context.window_h=0;

	if(!g_defultContextIsAlreadySet){
		g_defultContext=context;
		g_defultContextIsAlreadySet=true;
	}
	loge("TICK INIT .");
	return context;
}








void BatcheRendrerAdd2DShape(float* vetex , u32 vcount , u32* index, u32 icount , TickContext* context){
	BatchRendringAddIndex(&context->Shape2D.indexbatchr, 
			&context->Shape2D.indexbatchSize,
			&context->Shape2D.indexbatchPtr,
			&context->Shape2D.isIndexChanged,
		 	index, icount, context->Shape2D.vertexbatchPtr, 4);
	BatchRendringAddVertex(&context->Shape2D.vertexbatchr,&context->Shape2D.vertexbatchSize , &context->Shape2D.vertexbatchPtr, &context->Shape2D.isVertexChanged 
			, vetex, vcount);
	return;
}









void DrawTriangle(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl)
{
	DrawTriangle_ctx(v1,  v2, v3, cl,&g_defultContext);
}



void DrawLine(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl){

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
		v3.x,v3.y,*(float*)&c,*(float*)&flage,
	};
	u32 indece[3]{0,(u32)1,(u32)2};//i know, this is reducled, but i am too lazy to think about a new way to do it with out a index count

	//u32 verty , indexy;
	//g_2DShapesBatchRenderer->Push(verteces,9,indece,3);
	BatcheRendrerAdd2DShape(verteces, sizeof(verteces)/sizeof(float), indece, 3, ctx);
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
		v4.x,v4.y,*(float*)&c,*(float*)&flage,
	};

	//g_2DShapesBatchRenderer->Push(verteces,sizeof(verteces)/sizeof(float),indeces,sizeof(indeces)/sizeof(u32));
	BatcheRendrerAdd2DShape(verteces, sizeof(verteces)/sizeof(float), indeces, sizeof(indeces)/sizeof(u32), ctx);
}
void DrawRectangel_ctx(float x, float y , float w , float h,Vec4c cl,TickContext* ctx){
	DrawQuadrilateral_ctx({x,y}, {x+w,y}, {x,y+h}, {x+w,y+h},  cl,ctx);
	return;
}


void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount , Vec4c cl,TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false,.textureSlot=0};
	

	float* Vertex = (float*)malloc((Vertecount*5)*sizeof(float));
	u32* indeces = (u32*)malloc(Vertecount*3*sizeof(u32));
	
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
	BatcheRendrerAdd2DShape(Vertex, Vertecount*4, indeces, Vertecount*3, ctx);
	free(Vertex);
	free(indeces);
	return;
}




void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount ,u32* indeces,u32 Indexcont, Vec4c cl,TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_TRINGELS,.Enbletextures=false,.textureSlot=0};


	float* Vertex = (float*)malloc((Vertecount*5)*sizeof(float));
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	for(u32 i = 0 ; i < Vertecount; i++){
		Vertex[i*4]=verteces[i].x;
		Vertex[i*4+1]=verteces[i].y;
		Vertex[i*4+2]=*(float*)&c;
		Vertex[i*4+3]=*(float*)&flage;
	}

	//g_2DShapesBatchRenderer->Push(Vertex,Vertecount*3,indeces,Indexcont);
	BatcheRendrerAdd2DShape(Vertex, Vertecount*4, indeces, Indexcont, ctx);
	free(Vertex);
	return;
}


void DrawCercel_ctx(float x , float y , float r, float steps , Vec4c cl, TickContext* ctx){
	VertexFlags flage{.Practicul=VERTFG_CERCULS,.Enbletextures=false,.textureSlot=0};
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;	
	
	float verteces[5];


//	BatcheRendrerAdd2DShape(verteces, sizeof(verteces)/sizeof(float), indeces, sizeof(indeces)/sizeof(u32), ctx);

	return;

}






/************************************** Rendrer ****************************************/




void TickRendre(GLFWwindow* window){
	TickRendre_ctx(window, &g_defultContext);

	return;
}


void TickNewFrame(){
	TickNewFrame_ctx(&g_defultContext);
	return;

}



bool regenRendrerData(TickRendrerStruct* rendr){
	bool isitChanged = true;
	if(rendr->isVertexChanged){
		if(rendr->vertexbatchPtr*sizeof(float)>rendr->VertexBufferSize){
			RegenrateVertexBuffer(&rendr->VertexBuffer,rendr->vertexbatchr,rendr->vertexbatchPtr*sizeof(float));
			rendr->VertexBufferSize=rendr->vertexbatchPtr*sizeof(float);
			
			//std::cout<<"\nRegnarate Vertex Buffer to " << context.VertexBuffer2DSize;
			isitChanged=true;
		}else {
			glBindBuffer(GL_ARRAY_BUFFER,rendr->VertexBuffer);
			glBufferSubData(GL_ARRAY_BUFFER,0,rendr->vertexbatchPtr*4,rendr->vertexbatchr);
		}
	}
	if(rendr->isIndexChanged){
		if(rendr->indexbatchPtr*sizeof(u32)>rendr->IndexBufferSize){
			RegenrateIndexBuffer(&rendr->IndexBuffer,rendr->indexbatchr,rendr->indexbatchPtr*sizeof(u32));

			rendr->IndexBufferSize=rendr->indexbatchPtr*sizeof(u32);
			//std::cout<<"\nRegnarate Index Buffer to " << context.IndexBuffer2DSize;
			isitChanged=true;
		}else {
			CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rendr->IndexBuffer));
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,rendr->indexbatchPtr*sizeof(u32),rendr->indexbatchr);
			
		}
	}
	return isitChanged;

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

	
	bool shapeChanged =  regenRendrerData(&context.Shape2D);
	bool circChanged  = regenRendrerData(&context.ShapeCir2D);	
	if(shapeChanged){
		RegenrateVetexArray(&context.Shape2D.VAO);
		GenrateAttribute2DShape(context.Shape2D.VAO, context.Shape2D.VertexBuffer, context.Shape2D.IndexBuffer);
	}
	if(circChanged){
		RegenrateVetexArray(&context.ShapeCir2D.VAO);
		GenrateAttribute2DShape(context.ShapeCir2D.VAO, context.ShapeCir2D.VertexBuffer, context.ShapeCir2D.IndexBuffer);
	}

	CHECK_GL_ERORR(glBindVertexArray(context.Shape2D.VAO));
	CHECK_GL_ERORR(glBindBuffer(GL_ARRAY_BUFFER,context.Shape2D.VertexBuffer));
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,context.Shape2D.IndexBuffer));
	
	CHECK_GL_ERORR(glDrawElements(GL_TRIANGLES, context.Shape2D.indexbatchPtr, GL_UNSIGNED_INT, nullptr));

	return;
}
void TickNewFrame_ctx(TickContext* context){
	context->Shape2D.indexbatchPtr=0;
	context->Shape2D.vertexbatchPtr=0;
	context->Shape2D.isVertexChanged=false;
	context->Shape2D.isIndexChanged=false;
	
	context->ShapeCir2D.indexbatchPtr=0;
	context->ShapeCir2D.vertexbatchPtr=0;
	context->ShapeCir2D.isVertexChanged=false;
	context->ShapeCir2D.isIndexChanged=false;
	return;
}


void TickClose(){
	if(g_defultContextIsAlreadySet){
		free(g_defultContext.Shape2D.indexbatchr);
		free(g_defultContext.Shape2D.vertexbatchr);
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
		free(context->Shape2D.indexbatchr);
		free(context->Shape2D.vertexbatchr);
	}
}
