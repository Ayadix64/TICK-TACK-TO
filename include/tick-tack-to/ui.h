#ifndef TICK_UI
#define TICK_UI
#include "utils.h"
#include <ctime>
#define UI_DEFAULT_BACKGROUND_COLOR {12,14,50 ,255}
#define UI_DEFAULT_HOUVER_COLOR     {20,24,70 ,255}
#define UI_DEFAULT_SELECT_COLOR     {24,28,128,255}

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

char Button  (const char* text,float x , float y ); //bit1: preased, bit2: hover
char TextBox (float x , float y , float w, TextBoxData* tbd);
void CheckBox(const char* bx ,float x , float y , char * b);
#endif
