static const char* g_2DShape_vertexshader = 
	"#version 330 core\n"
	"layout(location=0) in vec4 position;\n"
	"layout(location=1) in uint inColor;\n"
	"\n"
	"flat out uint color;\n"
	"uniform mat4 u_MVP;\n"
	"\n"
	"void main(){\n"
	"	gl_Position=u_MVP*position;\n"
	"	color=inColor;\n"
	"}\n"
	;


/********************************************g_2DShape_fragmentshader***********************************************/
static const char* g_2DShape_fragmentshader = 
	"#version 330 core\n"
	"layout(location=0) out vec4 outcl;\n"
	"flat in uint color;\n"
	"void main(){\n"
	"	float r = float((color>>24)&0xffu)/255.0;\n"
	"	float g = float((color>>16)&0xffu)/255.0;\n"
	"	float b = float((color>>8)&0xffu)/255.0;\n"
	"	float a = float(color&0xffu)/255.0;\n"
	"	\n"
	"	outcl =vec4(r,g,b,a);\n"
	"}\n"
	;
