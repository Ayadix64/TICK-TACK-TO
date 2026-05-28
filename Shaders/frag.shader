#version 330 core


layout(location=0) out vec4 outcl;


flat in uint color;

uniform sampler2D u_Texture;

void main(){
	float r = float((color>>24)&0xffu)/255.0;
	float g = float((color>>16)&0xffu)/255.0;
	float b = float((color>>8)&0xffu)/255.0;
	float a = float(color&0xffu)/255.0;

	vec4 cl = vec4(r,g,b,a);//texture(u_Texture,v_textCoord);
	outcl =cl;
}
