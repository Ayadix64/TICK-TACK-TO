#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in uint inColor;
layout(location=2) in uint Flags;
layout(location=3) in vec3 location3; // cneter of the cercul / texture 
// so , what ever tringel it passed; all what we will do is ortate it, whet ever position, to save the poor cpu frome some procesing cyculs

//out pos;
flat out uint color;
flat out uint flags;
out vec4 pos;
out vec2 texCoord;

uniform mat4 u_MVP;

vec2 Rotate(vec2 pos,vec2 center,float theta){
	float raduian=(theta*3.14159)/(180.0);
	float X = pos.x-center.x;
	float Y = pos.y-center.y;
	float posx=center.x+X*cos(raduian)-Y*sin(raduian);
	float posy=center.y+X*sin(raduian)+Y*cos(raduian);
	return vec2(posx,posy);
}


void main(){
	vec4 posi=position;
	if( (Flags & 0xfu) == uint(1)){
		posi.xy= Rotate(position.xy,location3.xy,location3.z); // the thread float of 'location3' will hold the theta
	}else if( (flags & 0x10u) > uint(0)){
		texCoord = location3.xy;
	}
	gl_Position=u_MVP*posi;
	pos=posi;
	flags=Flags;
	color=inColor;
}
