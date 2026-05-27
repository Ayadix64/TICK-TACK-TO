#version 330 core


layout(location=0) out vec4 outcl;


in float color;

uniform sampler2D u_Texture;

void main(){
	vec4 cl = vec4(1.0,0.0,0.0,1.0);//texture(u_Texture,v_textCoord);
	outcl =cl;
}
