#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <ostream>
#include <string>
#include "utils.h"
#include "shader.h"

unsigned int Shader::CompileShader(unsigned int type , const char* src){
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


unsigned int Shader::CreatShader(const char* vert, const char* frag){
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


Shader::Shader(const char* vs_path, const char* fs_path){
	std::string vs;
	std::string fs;
	readFile(vs_path, vs);
	readFile(fs_path, fs);
	
	m_shader = CreatShader(vs.c_str(), fs.c_str());
	Binde();
}


void Shader::Binde(){
	CHECK_GL_ERORR(glUseProgram(m_shader));
}


void Shader::UnBinde(){
	CHECK_GL_ERORR(glUseProgram(0));
}


unsigned int Shader::GetPrograme(){
	return m_shader;
}

int Shader::GetUniform(const char* uniform){
	int unfi = glGetUniformLocation(m_shader,uniform);
	if(unfi==-1){
		loge("WARNING","uniform \""+std::string(uniform)+"\" never found");
	}
	return unfi;
}

void Shader::SetUnifromF(const char* unif , unsigned int count, float* data){
	unsigned int uniform = GetUniform(unif);
	if(uniform==-1){
		Eloge("can't set uniforme \"" + std::string(unif)+"\" (uniform not found)");	
		return;
	}
	switch (count) {
		case 1:
			glUniform1f(uniform , data[0]);
			break;
		case 2:
			glUniform2f(uniform,data[0],data[1]);
			break;
		case 3:
			glUniform3f(uniform,data[0],data[1],data[2]);
			break;
		case 4:
			glUniform4f(uniform,data[0],data[1],data[2],data[3]);
			break;
		default:
			Eloge("Uniform Un-Seported count");
	}
	return;

}



void Shader::SetUniform1f(const char* unif, float f1){
	int uniform = GetUniform(unif);
	if(uniform==-1){
		Eloge("can't set uniforme \"" + std::string(unif)+"\" (uniform not found)");	
		return;
	}
	glUniform1f(uniform , f1);
	return;
}


void Shader::SetUniform2f(const char* unif, float f1, float f2){
	int uniform = GetUniform(unif);
	if(uniform==-1){
		Eloge("can't set uniforme \"" + std::string(unif)+"\" (uniform not found)");	
		return;
	}
	glUniform2f(uniform , f1 , f2);
	return;
}


void Shader::SetUniform3f(const char* unif, float f1, float f2, float f3){
	int uniform = GetUniform(unif);
	if(uniform==-1){
		Eloge("can't set uniforme \"" + std::string(unif)+"\" (uniform not found)");	
		return;
	}
	glUniform3f(uniform , f1,f2,f3);
	return;
}


void Shader::SetUniform4f(const char* unif, float f1, float f2, float f3, float f4){
	int uniform = GetUniform(unif);
	if(uniform==-1){
		Eloge("can't set uniforme \"" + std::string(unif)+"\" (uniform not found)");	
		return;
	}
	glUniform4f(uniform , f1, f2, f3, f4);
	return;
}


void Shader::SetUniform1i(const char* unif, int i1){
	int uniform = GetUniform(unif);
	if(uniform==-1){
		Eloge("can't set uniforme \"" + std::string(unif)+"\" (uniform not found)");
		return;
	}
	glUniform1i(uniform , i1);
}


void Shader::SetUniformMat4f(const char* unif, glm::mat4& m4){
	int uniform = GetUniform(unif);
	if(uniform==-1){
		Eloge("can't set uniforme \"" + std::string(unif)+"\" (uniform not found)");	
		return;
	}
	glUniformMatrix4fv(uniform,1,GL_FALSE,&m4[0][0]);
	
}
Shader::~Shader(){
	if(m_shader){
		CHECK_GL_ERORR(glDeleteProgram(m_shader));
	}
	return;
}




/***************************** Unifrorms *********************************/

Uniform::Uniform(const char* unif, Shader& shader ){
	shader.Binde();
	this->m_shader = &shader;
	this->m_location=shader.GetUniform(unif);
	return;
}


void Uniform::Set1f(float f1){
	if(Check(f1)){
		glUniform1f(m_location, f1);
	}
}
void Uniform::Set2f(float f1, float f2){
	if(Check(f1,f2)){
		glUniform2f(m_location, f1,f2);
	}
}
void Uniform::Set3f(float f1, float f2, float f3){
	if(Check(f1,f2,f3)){
		glUniform3f(m_location, f1,f2,f3);
	}
}
void Uniform::Set4f(float f1, float f2, float f3, float f4){
	if(Check(f1,f2,f3,f4)){
		glUniform4f(m_location, f1,f2,f3,f4);
	}
}

void Uniform::Set1i(int i1){
	if(Check(i1)){
		glUniform1i(m_location,i1);
	}
}

void Uniform::SetMat4f(glm::mat4& m4){
	if(Check(m4)){
		glUniformMatrix4fv(m_location,1,GL_FALSE,&m4[0][0]);
	}
}


bool Uniform::Check(float f1){
	if(m_location==-1){
		return false;
	}
	if(m_lastF[0][0]==f1){
		return false;
	}else {
		m_lastF[0][0]=f1;
		return true;
	}
}
bool Uniform::Check(float f1 , float f2){
	if(m_location==-1){
		return false;
	}
	if(m_lastF[0][0]==f1){
		return false;
	}else if (m_lastF[0][1]==f2) {
		return false;
	}else {
		m_lastF[0][0]=f1;
		m_lastF[0][1]=f2;
		return true;
	}
}
bool Uniform::Check(float f1 , float f2 , float f3){
	if(m_location==-1){
		return false;
	}
	if(m_lastF[0][0]==f1){
		return false;
	}else if (m_lastF[0][1]==f2) {
		return false;
	}else if (m_lastF[0][2]==f3) {
		return false;
	}else {
		m_lastF[0][0]=f1;
		m_lastF[0][1]=f2;
		m_lastF[0][2]=f3;
		return true;
	}
}
bool Uniform::Check(float f1 , float f2 , float f3, float f4){
	if(m_location==-1){
		return false;
	}
	if(m_lastF[0][0]==f1){
		return false;
	}else if (m_lastF[0][1]==f2) {
		return false;
	}else if (m_lastF[0][2]==f3) {
		return false;
	}else if (m_lastF[0][3]==f4) {
		return false;
	}else {
		m_lastF[0][0]=f1;
		m_lastF[0][1]=f2;
		m_lastF[0][2]=f3;
		m_lastF[0][3]=f4;
		return true;
	}
}
bool Uniform::Check(int i1){
	if(m_location==-1){
		return false;
	}
	if(m_lastI==i1){
		return false;
	}else {
		m_lastI=i1;
		return true;
	}
}
bool Uniform::Check(glm::mat4& mt){
	if(m_location==-1){
		return false;
	}
	for(int i = 0 ; i < 4 ; i++){
		for(int ii = 0 ; ii<4 ; ii++){
			if(mt[i][ii]!=m_lastF[i][ii]){
				memcpy(&m_lastF[0][0], &mt[0][0],  sizeof(float)*4*4);
				return true;
			}
		}
	}
	return false;
}


Uniform::~Uniform(){/*nothing lol*/}
