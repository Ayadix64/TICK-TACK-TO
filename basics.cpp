#include "indexbuff.h"
#include "utils.h"
#include "basics.hpp"
#include "batch.hpp"
#include "vertexbuff.h"
#include "vertexarray.h"
#include "rendrer.hpp"
#include <cmath>
BatchRendrer<float> *g_2DShapesBatchRenderer;
VertexBuff* g_2DShapeVertexBuffer;
VertexArray* g_2DShapeVAO;
IndexBuff* g_2DShapeIndexBuffer;

typedef struct {float x,y;u32 c;} Vertex;


void TickInit(){
	g_2DShapesBatchRenderer= new BatchRendrer<float>(3);
	g_2DShapeVertexBuffer = new VertexBuff(nullptr,0);
	g_2DShapeIndexBuffer = new IndexBuff(nullptr,0);
	
	g_2DShapeVAO = new VertexArray();
	g_2DShapeVAO->Bind();
	g_2DShapeVertexBuffer->Bind();
	g_2DShapeIndexBuffer->Bind();
	g_2DShapeVAO->AddElement<float>(2);//x,y
	g_2DShapeVAO->AddElement<float>(1);//color
	g_2DShapeVAO->Layout();
	//Chef kiss
}

void DrawTriangle(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl)
{
	
	u32 c = ((int)cl.r<<24)|((int)cl.g<<16)|((int)cl.b<<8)|cl.a;
	float verteces[]{
		v1.x,v1.y,(float)c,
		v2.x,v2.y,(float)c,
		v3.x,v3.y,(float)c,
	};
	g_2DShapesBatchRenderer->Push(verteces,sizeof(verteces)/sizeof(float),nullptr,0);
}


void DrawLine(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl){
	float offsetFromeTheSenter = thicknis/2.0f;//we ant the center line to be align with the line that the user want
	if(v1.y == v2.y && v1.x == v2.x){
		return;//wont draw any way lol
	}else if(v1.y==v2.y){
		DrawQuadrilateral({v1.x,v1.y-offsetFromeTheSenter}, {v2.x,v2.y-offsetFromeTheSenter}, {v1.x,v1.y+offsetFromeTheSenter} , {v2.x,v2.y+offsetFromeTheSenter},  cl);
		std::cout<<"\nY=Y";
	}else if(v1.x==v2.x){
		DrawQuadrilateral({v1.x-offsetFromeTheSenter,v1.y}, {v2.x-offsetFromeTheSenter,v2.y}, {v1.x+offsetFromeTheSenter,v1.y} , {v2.x+offsetFromeTheSenter,v2.y},  cl);
		std::cout<<"\nX=X";
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
	float c = ((float*)&cl)[0];;//float(((u32)(cl.r&0xff)<<24) | ((u32)(cl.g&0xff)<<16) | ((u32)(cl.b&0xff)<<8) | (u32)(cl.a&0xff));
	
	float verteces[]{
		v1.x,v1.y,c,
		v2.x,v2.y,c,
		v3.x,v3.y,c,
		v4.x,v4.y,c
	};
	g_2DShapesBatchRenderer->Push(verteces,sizeof(verteces)/sizeof(float),indeces,sizeof(indeces)/sizeof(u32));
}
void DrawRectangel(float x, float y , float w , float h,Vec4c cl){
	DrawQuadrilateral({x,y}, {x+w,y}, {x,y+h}, {x+w,y+h},  cl);
	return;
}


		


void TickRendre(){
	bool isitChanged = false;
	static int points=0; 
	if(g_2DShapesBatchRenderer->isVertexChanged()){
		isitChanged=true;
		loge("vertex charnged");
		if(!points){std::cout<<"..";};
		if(points){std::cout<<"==";};
		
		points=!points;
		u32 count;
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
	

	RnedrerDraw(*g_2DShapeVAO,*g_2DShapeIndexBuffer);
	g_2DShapesBatchRenderer->resetPointers();	
}
