#include <stdio.h>


#ifndef GLAD_GL_IMPLEMENTATION 
	#include "../deps/glad/glad.h"
	#define GLAD_GL_IMPLEMENTATION
#endif

#include "../include/tick-tack-to.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

void GoodOldTesting(){
	u32 cl = 0xff0000ff;
	float veteces[]={
		0.0,100.0,*(float*)&cl,
		100.0,0.0,*(float*)&cl,
		100.0,100.0,*(float*)&cl
	};
	u32 indeces[]={0,1,2};
	u32 vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	u32 vb;
	glGenBuffers(1,&vb);
	glBindBuffer(GL_ARRAY_BUFFER,vb);
	glBufferData(GL_ARRAY_BUFFER,sizeof(veteces),veteces,GL_DYNAMIC_DRAW);
	u32 ib;
	glGenBuffers(1,&ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indeces),indeces,GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,3*4,0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,3*4,(void*)8);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vb);
	glDeleteBuffers(1,&ib);
	return;
}
void GoodOldTesting2(float z){
	u32 cl = 0xffff00ff;
	float veteces[]={
		0.0,100.0,z,*(float*)&cl,
		100.0,0.0,z,*(float*)&cl,
		100.0,100.0,z,*(float*)&cl
	};
	u32 indeces[]={0,1,2};
	u32 vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	u32 vb;
	glGenBuffers(1,&vb);
	glBindBuffer(GL_ARRAY_BUFFER,vb);
	glBufferData(GL_ARRAY_BUFFER,sizeof(veteces),veteces,GL_DYNAMIC_DRAW);
	u32 ib;
	glGenBuffers(1,&ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indeces),indeces,GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,4*4,0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,4*4,(void*)12);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vb);
	glDeleteBuffers(1,&ib);
	return;
}


void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

int abs(int val){
	return val & ~(1<<32);
}


int main()<%
	/****************************Init*************************/
	if(!glfwInit()){
		//Eloge("GLFW not init");
		return 1;
	}
	
	TickInitWindowFlags();
	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();	
	// During init, enable debug output
	//glEnable              ( GL_DEBUG_OUTPUT );
	//glDebugMessageCallback( MessageCallback, 0 );

	printf("\nOpenGL Version : %s\n" ,glGetString(GL_VERSION));
	
	
	TickInit(window);
	//glfwSwapInterval(0);
	


	/**********************************************************/





	int pw,ph ;
	glfwGetFramebufferSize(window, &pw, &ph);



	float x=20.0,y=400.0,z=1000.0f , r=2.0f, r2=0.0f;
	float segments = 100.0;
	float scale = 1.0f;
	u32 image[320*255]={0xffffffff};
	
	for(int i = 0 ; i < 255 ; i++ ){
			for(int ii = 0 ; ii < 320 ; ii++){
				int cl = ((i)&0xff) << 24 | ((i)&0xff) << 16 | ((i)&0xff) << 8 | (i)&0xff;
				image[i*320+ii] = cl;
			}
		}
	
	TickTexture2D otherertheRise = LoadTextureFromeFile("art002e009287~large.jpg");
	TickTexture2D animatedTextutr=LoadTexture(image, 320, 200, 4);
	TickFont fira = LoadFont("FiraCode.ttf",20);
	
	u8 animation=0;
	int adder=1;
	SetDefaultFont(&fira);

	
	double tflf = glfwGetTime ();
	TextBoxData tbd;
	InitTextBoxData(&tbd, 0);
	char FPS[100];
	bool check;
	float slid = 0.0f;
	float counter = 0.0f;
	while(!glfwWindowShouldClose(window) ){
		
		for(int i = 0 ; i < 255 ; i++ ){
			for(int ii = 0 ; ii < 320 ; ii++){
				int cl = ((abs((i+animation)-255/2)*2)&0xff) << 24 | 
					 ((abs((i+animation)-255/2)*2)&0xff) << 16 |
					 ((abs((i+animation)-255/2)*2)&0xff) << 8  |
					  (abs((i+animation)-255/2)*2)&0xff;
				image[i*320+ii] = cl;
		 	}
		}
		if(animation==255)adder=-1;
		if(animation==0)adder=1;
		animation+=adder;
		
	
		TickNewFrame();
			

		if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			x+=5.0f;
		}
		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			x-=5.0f;
		}
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			y-=5.0f;
		}
		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			y+=5.0f;
		}
		
		glfwMakeContextCurrent(window);
		

		DrawTexture(animatedTextutr, 0,0, 200, 200);
		DrawLine((Vec2f){0.0f,0.0f}, (Vec2f){200.0f,200.0f}, 20.0,(Vec4c){0,0,255,255});
		
		DrawCircle(200.0f, 200.0f, 10, 20, (Vec4c){0,0,255,255});
		
		DrawLine((Vec2f){200.0f,200.0f}, (Vec2f){x,y}, 20.0,(Vec4c){255,255,255,20});
		
		DrawText("the fast quick fox jump over the lazy slow\n--> ** dog **, or is it ?", 300, 200,(Vec4c){255,255,255,255});
		ReloadTexture(&animatedTextutr, image,300 , 250, 4);
		char butnflags = Button("Button\nThis is a hello world button\nor is it?", x, y,0,200);

		//Button("How is the dat of Kbnuib", 600, 600);
		if(butnflags&1){
			printf("CLICKED!\n");
			fflush(stdout);
		}else if(butnflags&2){
			printf("HOVER\n");
		}
		
		sprintf(FPS, "FPS: %d." , (u32)(1.0/((glfwGetTime()-tflf))));
		DrawText(FPS, 0, 0,(Vec4c){255,255,0,255});
		DrawEmptyRoundedRectangel(300+cos(counter)*80.0, 400+sin(counter)*40.0, 60, 60, 30, 20, 90, (Vec4c){255,255,0,255});
		DrawEmptyRoundedRectangel(300+cos(counter+3.14*0.5)*80.0, 400+sin(counter+3.14*0.5)*40.0, 60, 60, 30, 20, 90,(Vec4c) {255,255,0,255});
		DrawEmptyRoundedRectangel(300+cos(counter+3.14*1.0)*80.0, 400+sin(counter+3.14*1.0)*40.0, 60, 60, 30, 20, 90,(Vec4c) {255,255,0,255});
		DrawEmptyRoundedRectangel(300+cos(counter+3.14*1.5)*80.0, 400+sin(counter+3.14*1.5)*40.0, 60, 60, 30, 20, 90,(Vec4c) {255,255,0,255});
		

		TextBox( 20, 20,200,0, &tbd);


		CheckBox("Check Box Bora Broa Broa .", 20, 300, (char*)&check);
		
		
		if(check){
			printf("checked , slider : %f \n",slid);
		}
		Slider(200,500,300,&slid);
		//DrawCircle(GetMousePos().x, GetMousePos().y,5, 20, {0,255,0,255})	;

		/******************** Render ********************/
		TickRendre();
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		tflf=glfwGetTime () ;
		counter+=2.0f*slid+(sin(counter))*0.1;

	}
	
	glfwTerminate();
%>



