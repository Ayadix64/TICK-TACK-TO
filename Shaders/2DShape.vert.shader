#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in uint inColor;

layout(location=2) in uint Flags;



flat out uint color;
flat out uint flags;

out vec4 cercelPosX;
out vec4 cercelPosY;
out float Raduce;


uniform mat4 u_MVP;



void main(){
	gl_Position=u_MVP*position;
	if(Flags & 0xf){
		/*do somthing potansly cool*/
		if(gl_VertexID<4){
			cercelPosX[gl_VertexID]=position.x;
			cercelPosY[gl_VertexID]=position.y;
		}
	}
	color=inColor;
}
