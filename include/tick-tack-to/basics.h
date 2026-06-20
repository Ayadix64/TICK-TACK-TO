#ifndef TICK_BASICS
#define TICK_BASICS
#include "utils.h"
#include <cstddef>
#include <glm/ext/matrix_float4x4.hpp>
#include <GLFW/glfw3.h>



typedef struct{
	u32 VAO;
	u32 VertexBuffer;
	u32 VertexBufferSize;
	u32 IndexBuffer;
	u32 IndexBufferSize;
	
	float* vertexbatchr;
	u32 vertexbatchPtr;
	u32 vertexbatchSize;
	char isVertexChanged;

	u32  * indexbatchr;
	u32 indexbatchPtr;
	u32 indexbatchSize;
	char isIndexChanged;

}TickRendrerStruct;


typedef struct {
	u32 window_w,window_h;
	int Shader2D;
	TickRendrerStruct Shape2D;
	TickRendrerStruct ShapeCir2D;
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
void TickNewFrame();
void TickRendre(GLFWwindow* window);


void DrawTriangle_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl,TickContext* ctx);
void DrawRectangel_ctx(float x, float y , float w , float h,Vec4c cl,TickContext* ctx);
void DrawLine_ctx(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl,TickContext* ctx);
void DrawQuadrilateral_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl,TickContext* ctx);
void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount , Vec4c cl,TickContext* ctx);
void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount ,u32* indeces , u32 Indexcount , Vec4c cl,TickContext* ctx);
void DrawCercel_ctx(float x , float y , float r, float steps , Vec4c cl,TickContext* ctx);
void TickNewFrame_ctx(TickContext* context);
void TickRendre_ctx(GLFWwindow* window,TickContext* ctx);

#endif
