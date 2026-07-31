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
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;
uniform sampler2D texture9;
uniform sampler2D texture10;
uniform sampler2D texture11;
uniform sampler2D texture12;
uniform sampler2D texture13;
uniform sampler2D texture14;
uniform sampler2D texture15;
uniform sampler2D texture16;
uniform sampler2D texture17;
uniform sampler2D texture18;
uniform sampler2D texture19;
uniform sampler2D texture20;
uniform sampler2D texture21;
uniform sampler2D texture22;
uniform sampler2D texture23;
uniform sampler2D texture24;
uniform sampler2D texture25;
uniform sampler2D texture26;
uniform sampler2D texture27;
uniform sampler2D texture28;
uniform sampler2D texture29;
uniform sampler2D texture30;
uniform sampler2D texture31;
uniform sampler2D texture32;
void main(){
	float r = float((color>>24)&0xffu)/255.0;
	float g = float((color>>16)&0xffu)/255.0;
	float b = float((color>>8)&0xffu)/255.0;
	float a = float(color&0xffu)/255.0;
	
	if( (flags & 0x10u) > uint(0)){// it is a texture
		int tex = int((flags>>5)&0x1fu);
		if      (tex==0)  {outcl=texture(texture0  ,texCoord);}
		else if (tex==1)  {outcl=texture(texture1  ,texCoord);}
		else if (tex==2)  {outcl=texture(texture2  ,texCoord);}
		else if (tex==3)  {outcl=texture(texture3  ,texCoord);}
		else if (tex==4)  {outcl=texture(texture4  ,texCoord);}
		else if (tex==5)  {outcl=texture(texture5  ,texCoord);}
		else if (tex==6)  {outcl=texture(texture6  ,texCoord);}
		else if (tex==7)  {outcl=texture(texture7  ,texCoord);}
		else if (tex==8)  {outcl=texture(texture8  ,texCoord);}
		else if (tex==9)  {outcl=texture(texture9  ,texCoord);}
		else if (tex==10) {outcl=texture(texture10 ,texCoord);}
		else if (tex==11) {outcl=texture(texture11 ,texCoord);}
		else if (tex==12) {outcl=texture(texture12 ,texCoord);}
		else if (tex==13) {outcl=texture(texture13 ,texCoord);}
		else if (tex==14) {outcl=texture(texture14 ,texCoord);}
		else if (tex==15) {outcl=texture(texture15 ,texCoord);}
		else if (tex==16) {outcl=texture(texture16 ,texCoord);}
		else if (tex==17) {outcl=texture(texture17 ,texCoord);}
		else if (tex==18) {outcl=texture(texture18 ,texCoord);}
		else if (tex==19) {outcl=texture(texture19 ,texCoord);}
		else if (tex==20) {outcl=texture(texture20 ,texCoord);}
		else if (tex==21) {outcl=texture(texture21 ,texCoord);}
		else if (tex==22) {outcl=texture(texture22 ,texCoord);}
		else if (tex==23) {outcl=texture(texture23 ,texCoord);}
		else if (tex==24) {outcl=texture(texture24 ,texCoord);}
		else if (tex==25) {outcl=texture(texture25 ,texCoord);}
		else if (tex==26) {outcl=texture(texture26 ,texCoord);}
		else if (tex==27) {outcl=texture(texture27 ,texCoord);}
		else if (tex==28) {outcl=texture(texture28 ,texCoord);}
		else if (tex==29) {outcl=texture(texture29 ,texCoord);}
		else if (tex==30) {outcl=texture(texture30 ,texCoord);}
		else if (tex==31) {outcl=texture(texture31 ,texCoord);}
		
		outcl.r*=r;
		outcl.g*=g;
		outcl.b*=b;
		outcl.a*=a;
		
		//outcl.a=outcl.a*a+a*(1.0-a);
		//yeah that is auto generated, i know that this is not the best way to make it, opengl is aginst me rigth know
		//TODO: i dont even have to tell you what to do, bruh
		return;	
	}
	
	outcl =vec4(r,g,b,a);
	
}
