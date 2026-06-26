#version 330 core
layout(location=0) out vec4 outcl;


flat in uint color;

flat in uint flags;
in vec4 pos;
in vec2 texCoord;
/*flags bit structure
	|0123|  -> Praticul
	|4|     -> texture Enbled
	|56789| -> texture slot
	|10->31| ->reseved
*/

uniform sampler2D texture0;

void main(){
	
	
	if( (flags & 0x10u) == 0x10u){// it is a texture
		int tex = int(color);
		outcl=texture(texture0 ,texCoord);
		return;	
	}
	float r = float((color>>24)&0xffu)/255.0;
	float g = float((color>>16)&0xffu)/255.0;
	float b = float((color>>8)&0xffu)/255.0;
	float a = float(color&0xffu)/255.0;
	
	outcl =vec4(r,g,b,a);
	
}
