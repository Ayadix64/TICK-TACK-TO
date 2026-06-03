#include "indexbuff.h"
#include "utils.h"
#include "basics.hpp"
#include "batch.hpp"
#include "vertexbuff.h"
#include "vertexarray.h"
#include "rendrer.hpp"
#include <cmath>
#include <cstdlib>

BatchRendrer<float> *g_2DShapesBatchRenderer;
VertexBuff* g_2DShapeVertexBuffer;
VertexArray* g_2DShapeVAO;
IndexBuff* g_2DShapeIndexBuffer;

BatchRendrer<float> *g_2DImageBatchRenderer;
VertexBuff* g_2DImageVertexBuffer;
VertexArray* g_2DImageVAO;
IndexBuff* g_2DImageIndexBuffer;



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
	
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	float verteces[]{
		v1.x,v1.y,*(float*)&c,
		v2.x,v2.y,*(float*)&c,
		v3.x,v3.y,*(float*)&c,
	};
	u32 indece[3]{0,(u32)1,(u32)2};//i know, this is reducled, but i am too lazy to think about a new way to do it with out a index count

	//u32 verty , indexy;
	g_2DShapesBatchRenderer->Push(verteces,9,indece,3);
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

	g_2DShapesBatchRenderer->Push(verteces,sizeof(verteces)/sizeof(float),indeces,sizeof(indeces)/sizeof(u32));
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
	g_2DShapesBatchRenderer->Push(Vertex,Vertecount*3,indeces,Vertecount*3);
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

	g_2DShapesBatchRenderer->Push(Vertex,Vertecount*3,indeces,Indexcont);
	free(Vertex);
	return;
}


void DrawCercel(float x , float y , float r, u32 segments , Vec4c cl){
	if(!r)return;//it make no sence™ to a circel with out a raduice 
	float xx = r;
	float yy = 0.0;
	u32 c = cl.r << 24 | cl.g<<16 | cl.b << 8 | cl.a;
	/**********************************************************************************
	 *			TODO: this code is reduceles, fix it!
	 **********************************************************************************/
	float Verteces[8*3];
	u32 indeces[8*3];


	float ce_vertex[3]{x,y,*(float*)&c};

	g_2DShapesBatchRenderer->Push(ce_vertex,3,nullptr,0);

	for(u32 i = 1;xx>=r/1.5; yy+=(float)segments,i+=8){
		if(xx*xx+yy*yy-r*r>=0.0){
			xx-=(float)segments;
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
		
		g_2DShapesBatchRenderer->Push(Verteces,24,(u32*)indeces,12*4);	


			
		/*DrawRectangel((float)x+xx, (float)y+yy, 1.0f, 1.0f, cl);
		DrawRectangel((float)x+yy, (float)y+xx, 1.0f, 1.0f, cl);
		
		DrawRectangel((float)x-xx, (float)y+yy, 1.0f, 1.0f, cl);
		DrawRectangel((float)x-yy, (float)y+xx, 1.0f, 1.0f, cl);
		
		DrawRectangel((float)x+xx, (float)y-yy, 1.0f, 1.0f, cl);
		DrawRectangel((float)x+yy, (float)y-xx, 1.0f, 1.0f, cl);
		
		DrawRectangel((float)x-xx, (float)y-yy, 1.0f, 1.0f, cl);
		DrawRectangel((float)x-yy, (float)y-xx, 1.0f, 1.0f, cl);*/
		

		//DrawRectangel((float)x+yy, (float)y+xx, 1.0f, 1.0f, cl);
		//DrawRectangel((float)x-xx, (float)y+yy, 1.0, 1.0, cl);
		//DrawRectangel((float)x+xx, (float)y-yy, 1.0, 1.0, cl);
		//DrawRectangel((float)x-xx, (float)y-yy, 1.0, 1.0, cl);
	}
	//Draw2DVerteces((Vec2f*)Verteces, (u32)r*8 , cl);
	return;

}

void TickRendre(){
	bool isitChanged = false;
	static int points=0; 
	
	if(g_2DShapesBatchRenderer->isVertexChanged()){
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
	
	g_2DShapeVAO->Bind();
	
	CHECK_GL_ERORR(glDrawElements(GL_TRIANGLES, g_2DShapesBatchRenderer->GetIndexCount(), GL_UNSIGNED_INT, nullptr));

	g_2DShapesBatchRenderer->resetPointers();	
}
