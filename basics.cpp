#include "externel/imgui/imgui_impl_glfw.h"
#include "indexbuff.h"
#include "shader.h"
#include "utils.h"
#include "basics.hpp"
#include "batch.hpp"
#include "vertexbuff.h"
#include "vertexarray.h"
#include <GL/gl.h>
#include "shaders.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <atomic>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>

TickContext g_defultContext;
std::atomic<bool> g_defultContextIsAlreadySet;

#define debugy(x) std::cout<<"\n"<<#x<<" : " << x ;


/*BatchRendrer<float> *g_2DShapesBatchRenderer;
VertexBuff* g_2DShapeVertexBuffer;
VertexArray* g_2DShapeVAO;
IndexBuff* g_2DShapeIndexBuffer;
Shader* g_2DShapeShader;
Uniform* g_2DShape_u_MVP;


BatchRendrer<float> *g_2DImageBatchRenderer;
VertexBuff* g_2DImageVertexBuffer;
VertexArray* g_2DImageVAO;
IndexBuff* g_2DImageIndexBuffer;
*/


typedef struct {float x,y;u32 c;} Vertex;




TickContext TickInit(){
	//g_2DShapeShader = new Shader(g_2DShape_vertexshader,g_2DShape_fragmentshader);
	//g_2DShape_u_MVP = new Uniform("u_MVP",*g_2DShapeShader);

	//g_2DShapesBatchRenderer= new BatchRendrer<float>(3);
	//g_2DShapeVertexBuffer = new VertexBuff(nullptr,0);
	//g_2DShapeIndexBuffer = new IndexBuff(nullptr,0);
	
	//g_2DShapeVAO = new VertexArray();
	//g_2DShapeVAO->Bind();
	//g_2DShapeVertexBuffer->Bind()
	//g_2DShapeIndexBuffer->Bind();
	//g_2DShapeVAO->AddElement<float>(2);//x,y
	//g_2DShapeVAO->AddElement<float>(1);//color
	//g_2DShapeVAO->Layout();
	loge("TICK INIT ...");
	TickContext context;
	context.Shader2D= CreatShader(g_2DShape_vertexshader, g_2DShape_fragmentshader);
	glGenVertexArrays(1,&context.VAO_2D);
	context.VertexBuffer2D = GenVertexBuffer(nullptr, 0);
	context.VertexBuffer2DSize=0;
	context.IndexBuffer2D=GenIndexBuff(nullptr, 0);
	context.IndexBuffer2DSize=0;
	context.uniform2DMvp = GetUniform("u_MVP", context.Shader2D);		
	
	context.VAO_2D = GenVertexArray();
	CHECK_GL_ERORR(glBindVertexArray(context.VAO_2D));
	CHECK_GL_ERORR(glBindBuffer(GL_ARRAY_BUFFER,context.VertexBuffer2D));
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,context.IndexBuffer2D));
	GenVAAP(0, GL_FLOAT, false, 4,2, (void *)0);
	GenVAAP(1, GL_FLOAT, false, 4,1, (void *)(2*sizeof(float)));
	
	context.vertexbatch2DSize=0x1000;
	context.vertexbatchr2D = (float*)malloc(0x1000);
	context.vertexbatch2DPtr=0;

	context.indexbatch2DSize=0x1000;
	context.indexbatchr2D = (u32*)malloc(0x1000);
	context.indexbatch2DPtr=0;

	if(!g_defultContextIsAlreadySet){
		g_defultContext=context;	
		g_defultContextIsAlreadySet=true;
	}
	loge("TICK INIT .");
	return context;
}



void BatcheRendrerAdd(float* vetex , u32 vcount , u32* index, u32 icount , TickContext* context){
	BatchRendringAddIndex(&context->indexbatchr2D, &context->indexbatch2DSize, &context->indexbatch2DPtr, &context->isIndex2DChanged,
		 index, icount, context->vertexbatch2DPtr, 3);
	BatchRendringAddVertex(&context->vertexbatchr2D,&context->vertexbatch2DSize , &context->vertexbatch2DPtr, &context->isVertex2DChanged 
			, vetex, vcount);
	return;
}



void DrawTriangle(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl)
{
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	float verteces[]{
		v1.x,v1.y,*(float*)&c,
		v2.x,v2.y,*(float*)&c,
		v3.x,v3.y,*(float*)&c,
	};
	u32 indece[3]{0,(u32)1,(u32)2};//i know, this is reducled, but i am too lazy to think about a new way to do it with out a index count

	//u32 verty , indexy;
	//g_2DShapesBatchRenderer->Push(verteces,9,indece,3);
	BatcheRendrerAdd(verteces, 9, indece, 3, &g_defultContext);
}


void DrawLine(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl){
	float offsetFromeTheSenter = thicknis/2.0f;//we ant the center line to be align with the line that the user want
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
	}
	
	return;	
}

void DrawQuadrilateral(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl)// v1___v2
									 //  |   |
									 //  |   |
									 // v3"""v4
{
	u32 indeces[6]{
		0,1,2,
		2,3,1
	};
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;	
	float verteces[]{ 
		v1.x,v1.y,*(float*)&c,
		v2.x,v2.y,*(float*)&c,
		v3.x,v3.y,*(float*)&c,
		v4.x,v4.y,*(float*)&c
	};

	//g_2DShapesBatchRenderer->Push(verteces,sizeof(verteces)/sizeof(float),indeces,sizeof(indeces)/sizeof(u32));
	BatcheRendrerAdd(verteces, 12, indeces, 9, &g_defultContext);
}
void DrawRectangel(float x, float y , float w , float h,Vec4c cl){
	DrawQuadrilateral({x,y}, {x+w,y}, {x,y+h}, {x+w,y+h},  cl);
	return;
}


void Draw2DVerteces(Vec2f* verteces , u32 Vertecount , Vec4c cl){
	float* Vertex = (float*)malloc((Vertecount*3)*sizeof(float));
	u32* indeces = (u32*)malloc(Vertecount*3*sizeof(u32));
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	for(u32 i = 0 ; i < Vertecount; i++){
		Vertex[i*3]=verteces[i].x;
		Vertex[i*3+1]=verteces[i].y;
		Vertex[i*3+2]=*(float*)&c;
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
	BatcheRendrerAdd(Vertex, Vertecount*3, indeces, Vertecount*3, &g_defultContext);
	free(Vertex);
	free(indeces);
	return;
}




void Draw2DVerteces(Vec2f* verteces , u32 Vertecount ,u32* indeces,u32 Indexcont, Vec4c cl){
	float* Vertex = (float*)malloc((Vertecount*3)*sizeof(float));
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	for(u32 i = 0 ; i < Vertecount; i++){
		Vertex[i*3]=verteces[i].x;
		Vertex[i*3+1]=verteces[i].y;
		Vertex[i*3+2]=*(float*)&c;
	}

	//g_2DShapesBatchRenderer->Push(Vertex,Vertecount*3,indeces,Indexcont);
	BatcheRendrerAdd(Vertex, Vertecount*3, indeces, Indexcont, &g_defultContext);
	free(Vertex);
	return;
}


void DrawCercel(float x , float y , float r, float steps , Vec4c cl){
	if(!r|!steps)return;//it make no sence™ to a circel with out a raduice or a steps
	
	float xx = r;
	float yy = 0.0f;
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	/**********************************************************************************
	 *			TODO: this code is reduceles, fix it!
	 **********************************************************************************/
	float Verteces[8*3];
	u32 indeces[12];


	float ce_vertex[3]{x,y,*(float*)&c};

	//g_2DShapesBatchRenderer->Push(ce_vertex,3,nullptr,0);

	BatcheRendrerAdd(ce_vertex, 3, NULL, 0, &g_defultContext);
	for(u32 i = 1;xx>r/1.5f; yy+=steps,i+=8){
		if(xx*xx+yy*yy-r*r>0.0f){
			xx-=steps;
		}
	
		Verteces[0]=x+xx;
		Verteces[1]=y+yy;
		Verteces[2]=*(float*)&c;
		Verteces[3]=x+yy;
		Verteces[4]=y+xx;
		Verteces[5]=*(float*)&c;
	

		Verteces[6]=x+xx;
		Verteces[7]=y-yy;
		Verteces[8]=*(float*)&c;
		Verteces[9]=x+yy;
		Verteces[10]=y-xx;
		Verteces[11]=*(float*)&c;

		
		Verteces[12]=x-xx;
		Verteces[13]=y+yy;
		Verteces[14]=*(float*)&c;
		Verteces[15]=x-yy;
		Verteces[16]=y+xx;
		Verteces[17]=*(float*)&c;

		
		Verteces[18]=x-xx;
		Verteces[19]=y-yy;
		Verteces[20]=*(float*)&c;
		Verteces[21]=x-yy;
		Verteces[22]=y-xx;
		Verteces[23]=*(float*)&c;
		
		indeces[0]=-i;
		indeces[1]=0;
		indeces[2]=1;

		indeces[3]=-i;
	 	indeces[4]=2;
		indeces[5]=3;
	
		indeces[6]=-i;
		indeces[7]=4;
		indeces[8]=5;
	
		indeces[9]=-i;
		indeces[10]=6;
		indeces[11]=7;
		
		//g_2DShapesBatchRenderer->Push(Verteces,24,(u32*)indeces,12);	
		BatcheRendrerAdd(Verteces, 24, (u32*)indeces,12, &g_defultContext);
		//*/
		
		/*	
		DrawRectangel((float)x+xx, (float)y+yy, 1.0f, 1.0f, cl);
		DrawRectangel((float)x+yy, (float)y+xx, 1.0f, 1.0f, cl);
		
		DrawRectangel((float)x-xx, (float)y+yy, 1.0f, 1.0f, cl);
		DrawRectangel((float)x-yy, (float)y+xx, 1.0f, 1.0f, cl);
		
		DrawRectangel((float)x+xx, (float)y-yy, 1.0f, 1.0f, cl);
		DrawRectangel((float)x+yy, (float)y-xx, 1.0f, 1.0f, cl);
		
		DrawRectangel((float)x-xx, (float)y-yy, 1.0f, 1.0f, cl);
		DrawRectangel((float)x-yy, (float)y-xx, 1.0f, 1.0f, cl);
		//*/
		

		//DrawRectangel((float)x+yy, (float)y+xx, 1.0f, 1.0f, cl);
		//DrawRectangel((float)x-xx, (float)y+yy, 1.0, 1.0, cl);
		//DrawRectangel((float)x+xx, (float)y-yy, 1.0, 1.0, cl);
		//DrawRectangel((float)x-xx, (float)y-yy, 1.0, 1.0, cl);
	}
	//Draw2DVerteces((Vec2f*)Verteces, (u32)r*8 , cl);
	return;

}

void TickRendre(GLFWwindow* window){
	TickContext& context = g_defultContext;
	std::cout<<"\n\n*********************************************";
	debugy(context.VertexBuffer2D)
	debugy(context.VertexBuffer2DSize)
	debugy(context.vertexbatchr2D);
	debugy(context.vertexbatch2DPtr);
	debugy(context.vertexbatch2DSize)
	std::cout<<"\n";
	debugy(context.IndexBuffer2D)
	debugy(context.IndexBuffer2DSize)
	debugy(context.indexbatchr2D);
	debugy(context.indexbatch2DPtr);
	debugy(context.indexbatch2DSize)
	if(!g_defultContextIsAlreadySet){
		Eloge("Rendring without a Context ===> did you call TickInit() ?");
	}
	int bindedShader;
	//glGetIntegerv(GL_CURRENT_PROGRAM,&bindedShader);//we save wher ever shader is binded
	CHECK_GL_ERORR(glUseProgram(g_defultContext.Shader2D));	
	
	bool isitChanged = false;
	static int points=0; 
	
	if(context.isVertex2DChanged){
		if(context.vertexbatch2DPtr>context.VertexBuffer2DSize){
			RegenrateVertexBuffer(&context.VertexBuffer2D,context.vertexbatchr2D,context.vertexbatch2DPtr);
			context.VertexBuffer2DSize=context.vertexbatch2DPtr*sizeof(float);
			std::cout<<"\nRegnarate Vertex Buffer to " << context.VertexBuffer2DSize;
			isitChanged=true;
		}else {
			glBindBuffer(GL_ARRAY_BUFFER,context.VertexBuffer2D);
			FullVertexBuffer(context.vertexbatchr2D, context.vertexbatch2DPtr);
		}
		loge("vertex charnged");
		if(!points){std::cout<<"..";};
		if(points){std::cout<<"==";};
		
		points=!points;
	}
	if(context.isIndex2DChanged){
		if(context.indexbatch2DPtr>context.IndexBuffer2DSize){
			RegenrateIndexBuffer(&context.IndexBuffer2D,context.indexbatchr2D,context.indexbatch2DPtr);
			context.IndexBuffer2DSize=context.indexbatch2DPtr*sizeof(u32);
			std::cout<<"\nRegnarate Index Buffer to " << context.IndexBuffer2DSize;
			isitChanged=true;
		}else {
			CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,context.IndexBuffer2D));
			FullIndexBuff(context.indexbatchr2D, context.indexbatch2DPtr);
			
		}
		loge("index changed");
		u32 count;
		if(!points){std::cout<<"..";};
		if(points){std::cout<<"==";};
		
		points=!points;
	}
	if(isitChanged){
		RegenrateVetexArray(&context.VAO_2D);

		glBindVertexArray(context.VAO_2D);
		glBindBuffer(GL_ARRAY_BUFFER,context.VertexBuffer2D);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,context.IndexBuffer2D);
		
		GenVAAP(0, GL_FLOAT, false, 4,2, (void *)0);
		GenVAAP(1, GL_FLOAT, false, 4,1, (void *)(2*sizeof(float)));
		
	}
	int window_w, window_h;
	glfwGetFramebufferSize(window, &window_w, &window_h);

	glm::mat4 proj = glm::ortho(0.0f,(float)window_w , (float)window_h, 0.0f,-10.0f,10.0f);
	bool isProjDef = false;
	for(int i = 0 ; i < 4 ; i ++){
		for(int ii = 0 ; ii < 4 ; ii++){
			if(memcmp(&proj[i][ii],&context.prvuceMVP[i][ii],sizeof(float))){
				isProjDef=true;
				context.prvuceMVP[i][ii]=proj[i][ii];
			}
		}
	}

	if(isProjDef){
		CHECK_GL_ERORR(glUniformMatrix4fv(context.uniform2DMvp,1,GL_FALSE,&proj[0][0]));	
		loge("SETING MVP");
	}
	glBindVertexArray(context.VAO_2D);	
	CHECK_GL_ERORR(glDrawElements(GL_TRIANGLES, context.IndexBuffer2DSize/sizeof(u32), GL_UNSIGNED_INT, nullptr));

	context.indexbatch2DPtr=0;
	context.vertexbatch2DPtr=0;
	context.isVertex2DChanged=false;
	context.isIndex2DChanged=false;
	
	if(bindedShader && bindedShader!=-1){
	//	glUseProgram(bindedShader);
	}
	/*if(g_2DShapesBatchRenderer->isVertexChanged()){
		u32 count;
		isitChanged=true;
		loge("vertex charnged");
		if(!points){std::cout<<"..";};
		if(points){std::cout<<"==";};
		
		points=!points;
		void *vertaxData = g_2DShapesBatchRenderer->GetVertexData(count);
		g_2DShapeVertexBuffer->reFull(vertaxData, count*sizeof(float));
		std::cout<<" >>>>>>"<<count<<"\n";
	}
	if(g_2DShapesBatchRenderer->isIndexChanged()){
		isitChanged=true;
		loge("index changed");
		u32 count;
		if(!points){std::cout<<"..";};
		if(points){std::cout<<"==";};
		
		points=!points;
		void *indexData = g_2DShapesBatchRenderer->GetIndexData(count);
		g_2DShapeIndexBuffer->reFull(indexData, count*sizeof(u32));
		
	}
	if(isitChanged){
		g_2DShapeVAO->rebuild();
		g_2DShapeVertexBuffer->Bind();
		g_2DShapeIndexBuffer->Bind();
		g_2DShapeVAO->Layout();
	}
	g_2DShapeVAO->Bind();*/

}
