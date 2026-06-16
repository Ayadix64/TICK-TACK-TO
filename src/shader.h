#ifndef TICK_SHADER
#define TICK_SHADER
#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include "utils.h"
unsigned int CreatShader(const char* vert, const char* frag);
unsigned int CompileShader(unsigned int type , const char* src);
int GetUniform(const char* uniform, u32 shader);


#endif
