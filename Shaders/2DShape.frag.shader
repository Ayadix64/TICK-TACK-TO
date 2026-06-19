#version 330 core
layout(location=0) out vec4 outcl;


flat in uint color;
flat in uint flags;

in vec4 cercelPosX;
in vec4 cercelPosY;
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
		
	if( (flags) >= uint(1)){//it is a  cercul
		
		vec2 center = vec2((cercelPosX.x + cercelPosX.y)/2.0f , (cercelPosY.x + cercelPosY.y)/2.0f);//it all make sense, trust me bro
		float raduce = cercelPosX.x- center.x;
		float xVector = center.x - pos.x;
		float yVector = center.y - pos.y;
		if(xVector*xVector + yVector*yVector > raduce){
			return;
		}
		
	}
	if( (flags & 0x10u) == uint(1)){// it is a texture
		
		return;	
	}
	
	outcl =vec4(r,g,b,a);
	
}
