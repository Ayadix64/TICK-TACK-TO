#ifndef TICK_BASICS
#define TICK_BASICS
#include "utils.h"
#include <cstddef>
#include <glm/ext/matrix_float4x4.hpp>
#include <GLFW/glfw3.h>


#define TICK_MAX_TEXTURE_SLOTS_SEPURTED 32
typedef u32 textureSBitmap ;//slots bitmap
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
	u32 texture;
	textureSBitmap slotsbp;//slots 128 bitmap
	
	TickRendrerStruct rendrer;

} TickTextureRendrerStruct;


typedef struct {
	u32 window_w,window_h;
	float scaleX, scaleY;
	int Shader2D;
	TickRendrerStruct Shape2D;
	TickRendrerStruct ShapeCir2D;

	TickTextureRendrerStruct*textures;
	u32 textureCount;
	u32 texturesPtr;
	u32 maxTexturesSlotsSepurted;

	int uniform2DMvp;

}TickContext;


TickContext TickInit();


void SetScaleX(float scale);
void SetScaleY(float scale);
void SetScaleXY( float scalex, float scaley);
void SetScale( float scale);

void SetScaleX_ctx(TickContext* ctx, float scale);//bascly sete the context->scaleX to wwhat ever your number
void SetScaleY_ctx(TickContext* ctx, float scale);//the same thing
void SetScaleXY_ctx(TickContext* ctx, float scalex, float scaley);//...
void SetScale_ctx(TickContext* ctx, float scale);//...



void DrawQuadrilateral(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl);// v1___v2
									  //  |   |
									  //  |   |
									  // v3"""v4
void DrawTriangle(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl);
void DrawRectangel(float x, float y , float w , float h,Vec4c cl);
void DrawLine(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl);
void Draw2DVerteces(Vec2f* verteces , u32 Vertecount , Vec4c cl);
void Draw2DVerteces(Vec2f* verteces , u32 Vertecount ,u32* indeces , u32 Indexcount , Vec4c cl);
void DrawCircle(float x , float y , float r, float steps , Vec4c cl);
void TickNewFrame();
void TickRendre(GLFWwindow* window);


void DrawTriangle_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl,TickContext* ctx);
void DrawRectangel_ctx(float x, float y , float w , float h,Vec4c cl,TickContext* ctx);
void DrawLine_ctx(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl,TickContext* ctx);
void DrawQuadrilateral_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl,TickContext* ctx);
void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount , Vec4c cl,TickContext* ctx);
void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount ,u32* indeces , u32 Indexcount , Vec4c cl,TickContext* ctx);
void DrawCircle_ctx(float x , float y , float r, float steps , Vec4c cl,TickContext* ctx);
void TickNewFrame_ctx(TickContext* context);
void TickRendre_ctx(GLFWwindow* window,TickContext* ctx);



u32 LoadTexture(void* bitmap,float w, float h, u32 bpp);
u32 LoadTextureFromeFile(const char * fileName);
void DrawTexture(u32 index,float x , float y , float w,  float h );
void RemoveTexture(u32 index);
void ReloadTextureFromeFile(u32 index, const char* fileName);
void ReloadTexture(u32 index, void* data,u32 w , u32 h , u32 bpp );


u32 LoadTexture_ctx(void* bitmap,float w, float h, u32 bpp, TickContext* ctx);
u32 LoadTextureFromeFile_ctx(const char * fileName, TickContext *ctx);
void DrawTexture_ctx(u32 index,float x , float y , float w,  float h , TickContext* ctx);
void ReloadTexture_ctx(u32 index, void* data,u32 w , u32 h , u32 bpp , TickContext* ctx);
void ReloadTextureFromeFile_ctx(u32 index, const char* fileName, TickContext* ctx);
void RemoveTexture_ctx(u32 index, TickContext* ctx);

#endif
