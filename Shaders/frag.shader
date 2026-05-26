#version 330 core


layout(location=0) out vec4 outcl;


in vec2 v_textCoord;

uniform sampler2D u_Texture;

void main(){
	vec4 cl = vec4(v_textCoord.xy,1.0,0.5);//texture(u_Texture,v_textCoord);
	outcl =cl;
}
