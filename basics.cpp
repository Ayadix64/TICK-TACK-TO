#include "indexbuff.h"
#include "utils.h"
#include "basics.hpp"
#include "batch.hpp"
#include "vertexbuff.h"
#include "vertexarray.h"
#include "rendrer.hpp"
BatchRendrer<float> *g_2DShapesBatchRenderer;
VertexBuff* g_2DShapeVertexBuffer;
VertexArray* g_2DShapeVAO;
IndexBuff* g_2DShapeIndexBuffer;

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


void DrawQuadrilateral(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl)// v1___v2
									 //  |   |
									 //  |   |
									 // v3"""v4
{
	u32 indeces[6]{
		0,1,2,
		2,3,1
	};
	float c = (cl.r<<24)|(cl.g<<16)|(cl.b<<8)|cl.a;
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
	if(g_2DShapesBatchRenderer->isVertexChanged()){
		isitChanged=true;
		loge("vertex charnged");
		u32 count;
		void *vertaxData = g_2DShapesBatchRenderer->GetVertexData(count);
		g_2DShapeVertexBuffer->reFull(vertaxData, count*sizeof(float));
		for (int i = 0 ; i < count ; i++){
			std::cout<<((float*)vertaxData)[i]<<"\t";
		}
		std::cout<<" >>>>>>"<<count<<"\n";
	}
	if(g_2DShapesBatchRenderer->isIndexChanged()){
		isitChanged=true;
		loge("index changed");
		u32 count;
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
