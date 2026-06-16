#ifndef TICK_BASICS
#define TICK_BASICS
#include "utils.h"
#include <cstddef>
#include <glm/ext/matrix_float4x4.hpp>



typedef struct {
	
	u32 window_w,window_h;

	int Shader2D;
	u32 VAO_2D;
	u32 VertexBuffer2D;
	u32 VertexBuffer2DSize;
	u32 IndexBuffer2D;
	u32 IndexBuffer2DSize;
	
	float* vertexbatchr2D;
	u32 vertexbatch2DPtr;
	u32 vertexbatch2DSize;
	char isVertex2DChanged;

	u32  * indexbatchr2D;
	u32 indexbatch2DPtr;
	u32 indexbatch2DSize;
	char isIndex2DChanged;
	
	int uniform2DMvp;

}TickContext;


TickContext TickInit();

void DrawQuadrilateral(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl);// v1___v2
									  //  |   |
									  //  |   |
									  // v3"""v4
void DrawTriangle(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl);
void DrawRectangel(float x, float y , float w , float h,Vec4c cl);
void DrawLine(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl);
void Draw2DVerteces(Vec2f* verteces , u32 Vertecount , Vec4c cl);
void Draw2DVerteces(Vec2f* verteces , u32 Vertecount ,u32* indeces , u32 Indexcount , Vec4c cl);
void DrawCercel(float x , float y , float r, float steps , Vec4c cl);
void TickRendre(GLFWwindow* window);


void DrawTriangle_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl,TickContext* ctx);
void DrawRectangel_ctx(float x, float y , float w , float h,Vec4c cl,TickContext* ctx);
void DrawLine_ctx(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl,TickContext* ctx);
void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount , Vec4c cl,TickContext* ctx);
void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount ,u32* indeces , u32 Indexcount , Vec4c cl,TickContext* ctx);
void DrawCercel_ctx(float x , float y , float r, float steps , Vec4c cl,TickContext* ctx);
void TickRendre_ctx(GLFWwindow* window,TickContext* ctx);

#endif
