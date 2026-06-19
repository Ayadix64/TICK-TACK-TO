#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in uint inColor;
layout(location=2) in uint startID;
layout(location=2) in uint Flags;


//out pos;
flat out uint color;
flat out uint flags;

out vec4 cercelPosX;
out vec4 cercelPosY;
out float Raduce;
out vec4 pos;

uniform mat4 u_MVP;



void main(){
	gl_Position=u_MVP*position;
	pos=gl_Position;
	if( (Flags & 0xfu) == uint(1)){
		/*do somthing potansly cool*/
		if((startID)==uint(0)){
			cercelPosX.x=position.x;
			cercelPosY.x=position.y;
		}
		else if((startID)==uint(1)){
			cercelPosX.y=position.x;
			cercelPosY.y=position.y;
		}
		else if((startID)==uint(2)){
			cercelPosX.z=position.x;
			cercelPosY.z=position.y;
		}
		else if((startID)==uint(3)){
			cercelPosX.w=position.x;
			cercelPosY.w=position.y;
		}
	}
	flags=Flags;
	color=inColor;

}
