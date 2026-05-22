#version 330 core
layout(location=0) in vec4 position;//pleze read vec4 (for the better, and it convert it automaticly),at index 0
layout(location=1) in vec2 TextCoord;
out vec2 v_textCoord;
uniform mat4 u_MVP;
void main(){
	gl_Position=u_MVP*position;
	v_textCoord=TextCoord;
}
