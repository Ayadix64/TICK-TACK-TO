cmake_minimum_required(VERSION 3.16)
project(main)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug) #remeber to delet this if you want a user app, this increase the app length to better debug

find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(main main.cpp shader.cpp vertexbuff.cpp indexbuff.cpp vertexarray.cpp texture.cpp batch.cpp utils.cpp basics.cpp
externel/imgui/imgui.cpp externel/imgui/imgui_demo.cpp externel/imgui/imgui_draw.cpp externel/imgui/imgui_tables.cpp externel/imgui/imgui_widgets.cpp externel/imgui/imgui_impl_glfw.cpp externel/imgui/imgui_impl_opengl3.cpp )

#configure_folders(${CMAKE_CURRENT_SOURCE_DIR}/Shaders ${CMAKE_CURRENT_BINARY_DIR}/Shaders COPYONLY) #copying Shaders folder
#add_custom_target(shaders
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#	"${CMAKE_CURRENT_SOURCE_DIR}/Shaders/"
#	"${CMAKE_CURRENT_BINARY_DIR}/Shaders"	
#	COMMENT "Copying Shaders"
#)
#add_custom_command(
#	TARGET main POST_BUILD
#	COMMAND ./f2h  "$<TARGET_FILE:Shaders/>"
#                       "$<TARGET_FILE:myExe>.hash"
#	VERBATIM
#)


#add_dependencies(main shaders)


target_link_libraries(main glfw)
target_link_libraries(main OpenGL::GL GLEW)
add_compile_options( -DGLEW_EGL) #for wayland (linux)
