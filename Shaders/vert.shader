#version 330 core
layout(location=0) in vec4 position;//pleze read vec4 (for the better, and it convert it automaticly),at index 0
layout(location=1) in float inColor;

out float color;
uniform mat4 u_MVP;
uniform float u_z;
void main(){
	gl_Position=u_MVP*vec4(position.xyz,u_z);
	color=inColor;
}
