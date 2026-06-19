#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in uint inColor;
layout(location=2) in uint Flags;
layout(location=3) in uint startID;

//out pos;
flat out uint color;
flat out uint flags;

out vec4 cercelPosX;
out vec4 cercelPosY;
out vec4 pos;

uniform mat4 u_MVP;



void main(){
	gl_Position=u_MVP*position;
	pos=position;
	if( (Flags & 0xfu) == uint(1)){
		/*do somthing potansly cool*/
		if((startID)==uint(0)){
			cercelPosX.x=200.0;
			cercelPosY.x=200.0;
		}
		else if((startID)==uint(1)){
			cercelPosX.y=200.0;
			cercelPosY.y=400.0;
		}
		else if((startID)==uint(3)){
			cercelPosX.z=400.0;
			cercelPosY.z=200.0;
		}
		else if((startID)==uint(4)){
			cercelPosX.w=400.0;
			cercelPosY.w=400.0;
		}
	}
	flags=Flags;
	color=inColor;

}
