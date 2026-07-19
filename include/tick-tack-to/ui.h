#ifndef TICK_UI
#define TICK_UI
#include "utils.h"
#include <ctime>
#define UI_DEFAULT_BACKGROUND_COLOR {0x9,0x16,0x56,0xff} //#091656
#define UI_DEFAULT_HOUVER_COLOR     {0x12,0x2c,0xaf ,255} //#122caf
#define UI_DEFAULT_SELECT_COLOR     {0x20,0x41,0xe8,255} //#2041e8

typedef struct {
	u32 size;
	u32 maxsize;
	u32 usedsize;
	
	u32 pos;
	u32 xoffset;
	struct {
		char EnableNumbers:1;
		char EnbleCharctures:1;
		char Password:1;
	} flags;
	
	char* data;
}TextBoxData;

void InitTextBoxData(TextBoxData* tbd,u32 maxsize);

char Button  (const char* text,u32 x , u32 y ); //bit1: preased, bit2: hover
char TextBox (u32 x , u32 y , u32 w, TextBoxData* tbd);
void CheckBox(const char* bx ,u32 x , u32 y , char* b);
char Slider(u32 x , u32 y , u32 w,  float* s);
#endif
