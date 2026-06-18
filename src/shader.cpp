#include <iostream>
#include "utils.h"
#include "shader.h"

unsigned int CompileShader(unsigned int type , const char* src){
	unsigned int sh = glCreateShader(type);
	glShaderSource(sh,1,&src,nullptr);
	glCompileShader(sh);
	//debuging
	int err;
	glGetShaderiv(sh,GL_COMPILE_STATUS , &err);
	if(!err){
		int len;
		glGetShaderiv(sh,GL_INFO_LOG_LENGTH,&len);
		char* errmsg = (char*)malloc(len);
		glGetShaderInfoLog(sh,len,&len,errmsg);
		loge("*** "+std::string(type==GL_VERTEX_SHADER?"VERTAX":type==GL_FRAGMENT_SHADER?"FRAGMENT":"UKNOWN")+" SHADER ERORR ***");
		std::cout<<"===>>\n"<<errmsg<<"===>>END\n";
		return 0;
	}
	return sh;
}


unsigned int CreatShader(const char* vert, const char* frag){
	unsigned int prog = glCreateProgram();
	
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,vert);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,frag);
	CHECK_GL_ERORR(glAttachShader(prog,vs));
	CHECK_GL_ERORR(glAttachShader(prog,fs));
	
	CHECK_GL_ERORR(glLinkProgram(prog));
	CHECK_GL_ERORR(glValidateProgram(prog));

	CHECK_GL_ERORR(glDeleteShader(vs));
	CHECK_GL_ERORR(glDeleteShader(fs));
	return prog;
}



int GetUniform(const char* uniform, u32 shader){
	int uniformLocation=glGetUniformLocation(shader,uniform);
	if(uniformLocation==-1){
		Wloge("uniform \""+std::string(uniform)+"\" never found");
	}
	return uniformLocation;
}
