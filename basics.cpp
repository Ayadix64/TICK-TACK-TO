#include "utils.h"
#include "basics.hpp"

unsigned int tick_calledTimes = 0;
unsigned int tick_callingTurn= 0;

unsigned int tick_verteces_used=0;


void Called(){
	tick_callingTurn++;
	
	return;
}

void DrawSquar(){
	Called();
	return;
}


void Rendre(){
	tick_calledTimes=tick_callingTurn;
}
