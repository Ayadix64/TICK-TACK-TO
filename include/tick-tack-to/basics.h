#ifndef TICK_BASICS
#define TICK_BASICS
#include "utils.h"
#include <cstddef>
#include <GLFW/glfw3.h>
#include <ctime>



#define TICK_TOP_Z 0.0f  //the top z level
#define TICK_BUTTOM_Z -1.0f //the buttom z level
//for some reasen, opengl can display negative z cordnat as long as they are greater than -1.0, i will not ask why.
#define TICK_Z_OFSSET 0.001f // the amount of Z getting reduced in evry draw
#define TICK_MAX_DRAWING TICK_TOP_Z/TICK_Z_OFSSET


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
	u32 texture[TICK_MAX_TEXTURE_SLOTS_SEPURTED];
		
	TickRendrerStruct rendrer;

} TickTextureRendrerStruct;


typedef struct {
	GLFWwindow* window;
	u32 window_w,window_h;
	float scaleX, scaleY;
	int Shader2D;
	TickRendrerStruct Shape2D;
	TickRendrerStruct ShapeCir2D;

	TickTextureRendrerStruct* samplers;
	u32 samplerCount;
	u32 samplerPtr;
	u32 maxTexturesSlotsSepurted;

	int uniform2DMvp;
	float Z; // the zed of elements; for evry element been drawn, this will enable drawing batching with drawing ordring for textures
	
	u32 mousex,mousey;
	double lastClick;
	u8 mousemensions;//LeftC&Released , RightC&Released, LDouleClicked , LeftPress, RigthPress
	
	u32 lastKeyPress; //NOTE: this is NOT regsterd automaticly; 
			  //this is the last key been used by GetKeyPress_ctx/GetPressKey and it used for repeat time , 
			  //If you want to know the last key press, use the functions this lib provided / glfw provided, 
			  //this valu is not what you need!
	double lastKeyPressTime;
	


	char selectedInThisFaild;
	u32  selectCount;
	u32  selectID;
	u32  highlightedElement;

}TickContext;

typedef struct {
	u32 index , w , h , bpp;
}TickTexture2D;

/***************************Tick stuff******************************/
TickContext TickInit(GLFWwindow* window);
TickContext*GetDefaultContext();
void TickInitWindowFlags();

void TickSetWindow(GLFWwindow* window);
void TickSetWindow_ctx(GLFWwindow* window , TickContext* ctx);

void TickNewFrame();
void TickRendre();

void TickNewFrame_ctx(TickContext* context);
void TickRendre_ctx(TickContext* ctx);


void TickClose();
void TickClose_ctx(TickContext* context);

/*************************** Input ********************************/


Vec2i GetMousePos();
Vec2i GetMousePos_ctx(TickContext* ctx);

u32 GetMouseClickes();/*bit1 LeftBClickAndReleasd, bit2 RightBClickAndReleased, bit3 double click , 
			bit4 LBPress, bit5 RBPress; the click is one time and it will set to zero*/
u32 GetMouseClickes_ctx(TickContext* ctx);/*bit1 LeftBClick, bit2 RightBClick, bit3 double click ,
					    bit4 LBPress, bit5 RBPress; the click is one time and it will set to zero*/

u32 GetLastKey_ctx(TickContext* ctx);
u32 GetLastKey();

char GetKeyPressed(u32 k);
char GetKeyPressed_ctx(u32 k,TickContext* ctx);
char IsKeyPressed(u32 k);
char IsKeyPressed_ctx(u32 k,TickContext* ctx);


/*************************** Scaling ******************************/
void SetScaleX(float scale);
void SetScaleY(float scale);
void SetScaleXY( float scalex, float scaley);
void SetScale( float scale);

void SetScaleX_ctx(TickContext* ctx, float scale);//bascly sete the context->scaleX to wwhat ever your number
void SetScaleY_ctx(TickContext* ctx, float scale);//the same thing
void SetScaleXY_ctx(TickContext* ctx, float scalex, float scaley);//...
void SetScale_ctx(TickContext* ctx, float scale);//...

/*******************************************************************/


void DrawQuadrilateral(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl);// v1___v2
									  //  |   |
									  //  |   |
									  // v3"""v4
void DrawTriangle(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl);
void DrawRectangel(float x, float y , float w , float h,Vec4c cl);
void DrawLine(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl);
void Draw2DVerteces(Vec2f* verteces , u32 Vertecount , Vec4c cl);
void Draw2DVerteces(Vec2f* verteces , u32 Vertecount ,u32* indeces , u32 Indexcount , Vec4c cl);
void DrawCircle(float x , float y , float r, float segments , Vec4c cl);
void DrawCircleSector(float x , float y , float r, float segmetDegree , float segmentsDegreeStart, float segments , Vec4c cl);
/*	startDegree (0° on this case)
 *      __
 *      | ^,   the segmentDgree(90° in this case)
 *     r|   \
 *     y|___|
 * 	x
 * hope that this is straid forwared*/

void DrawEmptyCircle(float x , float y , float r,float thicknis, float segments , Vec4c cl);
void DrawEmptyCircleSector(float x , float y , float r,float thicknis, float segmetDegree, float segmentsDegreeStart ,float segments , Vec4c cl);
void DrawRoundedRectangel(float x, float y , float w , float h,float r , float segments ,Vec4c cl);
void DrawEmptyRoundedRectangel(float x, float y , float w , float h,float r , float thickness, float segments ,Vec4c cl);




void DrawTriangle_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 ,Vec4c cl,TickContext* ctx);
void DrawRectangel_ctx(float x, float y , float w , float h,Vec4c cl,TickContext* ctx);
void DrawLine_ctx(Vec2f v1 , Vec2f v2 , float thicknis , Vec4c cl,TickContext* ctx);
void DrawQuadrilateral_ctx(Vec2f v1 , Vec2f v2, Vec2f v3 , Vec2f v4,Vec4c cl,TickContext* ctx);
void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount , Vec4c cl,TickContext* ctx);
void Draw2DVerteces_ctx(Vec2f* verteces , u32 Vertecount ,u32* indeces , u32 Indexcount , Vec4c cl,TickContext* ctx);
void DrawCircle_ctx(float x , float y , float r, float segments , Vec4c cl,TickContext* ctx);
void DrawCircleSector_ctx(float x , float y , float r, float segmetDegree , float segmentsDegreeStart, float segments , Vec4c cl, TickContext* ctx);
/*	startDegree (0° on this case)
 *      __
 *      | ^,   the segmentDgree(90° in this case)
 *     r|   \
 *     y|___|
 * 	x
 * hope that this is straid forwared*/
void DrawEmptyCircle_ctx(float x , float y , float r,float thicknis, float segments , Vec4c cl, TickContext* ctx);
void DrawEmptyCircleSector_ctx(float x , float y , float r,float thicknis, float segmetDegree, float segmentsDegreeStart ,float segments , Vec4c cl, TickContext* ctx);
void DrawRoundedRectangel_ctx(float x, float y , float w , float h,float r , float segments ,Vec4c cl,TickContext* ctx);
void DrawEmptyRoundedRectangel_ctx(float x, float y , float w , float h,float r , float thickness, float segments ,Vec4c cl,TickContext* ctx);




TickTexture2D LoadTexture           (void* bitmap,float w, float h, u32 bpp);// load the texture to integer
TickTexture2D LoadTextureFromeFile  (const char * fileName);// load a texture from a file

void DrawTexture(TickTexture2D index,float x , float y , float w,  float h );
void DrawTextureSegment(TickTexture2D texture,float x , float y  , float w, float h ,float xx , float yy ,  float ww,  float hh );
void DrawTextureSegmentExtended(TickTexture2D texture,Vec2f v1 , Vec2f v2  , Vec2f v3, Vec2f v4 , Vec2f tc1 , Vec2f tc2 , Vec2f tc3 , Vec2f tc4 );

void RemoveTexture(TickTexture2D* index);
void ReloadTextureFromeFile(TickTexture2D *index, const char* fileName);
void ReloadTexture(TickTexture2D *index, void* data,u32 w , u32 h , u32 bpp );



TickTexture2D LoadTexture_ctx           (void* bitmap,float w, float h, u32 bpp, TickContext* ctx);
TickTexture2D LoadTextureFromeFile_ctx  (const char * fileName, TickContext *ctx);

void DrawTexture_ctx           (TickTexture2D index,float x , float y , float w,  float h , TickContext* ctx);
void DrawTextureSegment_ctx(TickTexture2D texture,float x , float y  , float w, float h ,float xx , float yy ,  float ww,  float hh , TickContext* ctx);
void DrawTextureSegmentExtended_ctx     (TickTexture2D texture,Vec2f v1 , Vec2f v2  , Vec2f v3, Vec2f v4 ,
					 Vec2f tc1 , Vec2f tc2 , Vec2f tc3 , Vec2f tc4, TickContext* ctx);

void ReloadTexture_ctx         (TickTexture2D* index, void* data,u32 w , u32 h , u32 bpp , TickContext* ctx);
void ReloadTextureFromeFile_ctx(TickTexture2D* index, const char* fileName, TickContext* ctx);
void RemoveTexture_ctx         (TickTexture2D* index, TickContext* ctx);

#endif
