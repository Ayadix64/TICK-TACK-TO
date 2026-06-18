#version 330 core
layout(location=0) out vec4 outcl;


flat in uint color;

flat in uint flags;

in vec4 cercelPosX;
in vec4 cercelPosY;
in float Raduce;
in vec4 pos;



/*flags bit structure
	|0123|  -> Praticul
	|4|     -> texture Enbled
	|56789| -> texture slot
	|10->31| ->reseved
*/



void main(){
	float r = float((color>>24)&0xffu)/255.0;
	float g = float((color>>16)&0xffu)/255.0;
	float b = float((color>>8)&0xffu)/255.0;
	float a = float(color&0xffu)/255.0;
	
	vec4 color;
		
	/*if( (flags & 0xfu) == uint(1)){//a cercul
		vec4 cercul;
		//if(gl_Position.x > 2.0){}
		
	}
	if( (flags & 0x10u) == uint(1)){// it is a texture
		return;	
	}*/
	
	outcl =vec4(r,g,b,a);
	
}
