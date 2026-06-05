#ifndef TICK_SHADER
#define TICK_SHADER
#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <glm/glm.hpp>
class Shader{
private:
	unsigned int m_shader;
	unsigned int CreatShader(const char* vert, const char* frag);
	unsigned int CompileShader(unsigned int type , const char* src);
public:
	Shader(const char* vs, const char* fs);
	~Shader();
	void Binde();
	void UnBinde();
	unsigned int GetPrograme();
	int GetUniform(const char* uniform);
	void SetUnifromF(const char* unif,unsigned int count ,float* data);//the maximum is 4
	void SetUniform1f(const char* unif, float f1);
	void SetUniform2f(const char* unif, float f1, float f2);
	void SetUniform3f(const char* unif, float f1, float f2, float f3);
	void SetUniform4f(const char* unif, float f1, float f2, float f3, float f4);

	void SetUniform1i(const char* unif, int i1);

	void SetUniformMat4f(const char* unif, glm::mat4& m4);
};


Shader GetShaderFromeFile(const char* vs_path, const char* fs_path);

class Uniform{
private:
	unsigned int m_location=0;
	Shader* m_shader=nullptr;
	float m_lastF[4][4];
	int m_lastI=0;
	bool Check(float f1);
	bool Check(float f1 , float f2);
	bool Check(float f1 , float f2 , float f3);
	bool Check(float f1 , float f2 , float f3, float f4);
	bool Check(int i1);
	bool Check(glm::mat4& mt);


public:
	Uniform(const char * unif, Shader& shader);
	~Uniform();

	void Set1f(float f1);
	void Set2f(float f1, float f2);
	void Set3f(float f1, float f2, float f3);
	void Set4f(float f1, float f2, float f3, float f4);

	void Set1i(int i1);

	void SetMat4f(glm::mat4& m4);

};
#endif
