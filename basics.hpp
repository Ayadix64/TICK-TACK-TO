#ifndef TICK_BASICS
#define TICK_BASICS
#include "utils.h"
void TickInit();

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
void TickRendre();
#endif
