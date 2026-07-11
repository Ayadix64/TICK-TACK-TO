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
	u32 pos;
	u32 xoffset;
	struct {
		char EnableNumbers:1;
		char EnbleCharctures:1;
	} flags;
	clock_t flickers;
	char* data;
}TextBoxData;

void InitTextBoxData(TextBoxData* tbd,u32 maxsize);

char DrawButton(const char* text,float x , float y ); //bit1: preased, bit2: hover
char TextBox(const char* text,float x , float y , float w, TextBoxData* tbd);
#endif
