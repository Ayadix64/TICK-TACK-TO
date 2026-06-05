#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in uint inColor;

flat out uint color;
uniform mat4 u_MVP;

void main(){
	gl_Position=u_MVP*position;
	color=inColor;
}
