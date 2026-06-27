##Hello!
# dont worry, you dont have to use f2h or to have it
# this is help me to convert the most freandly text format to the const char* format in src/shaders.h
# this Makefile will NOT run wats ever in the building, it used to update the real shaders in src/shaders.h in the devloping proces
# have a nice day
shaders:
	f2h 2DShape.vert.shader ../src/shaders.h g_2DShape_vertexshader
	f2h 2DShape.frag.shader ../src/shaders.h g_2DShape_fragmentshader -a
	echo "//Converted by File2.H!" >> ../src/shaders.h
