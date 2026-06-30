cmake_minimum_required(VERSION 3.16)
project(main)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug) #remeber to delet this if you want a user app, this increase the app length to better debug

find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)

add_executable(main main.cpp src/core.cpp src/utils.cpp src/basics.cpp src/render.cpp src/text.cpp
 externel/imgui/imgui.cpp externel/imgui/imgui_demo.cpp externel/imgui/imgui_draw.cpp externel/imgui/imgui_tables.cpp externel/imgui/imgui_widgets.cpp externel/imgui/imgui_impl_glfw.cpp externel/imgui/imgui_impl_opengl3.cpp )


target_link_libraries(main glfw)
target_link_libraries(main OpenGL::GL GLEW)
target_link_libraries(main ${FREETYPE_LIBRARIES})
target_include_directories(main PRIVATE ${FREETYPE_INCLUDE_DIRS})

add_compile_options( -DGLEW_EGL) #for wayland (linux)
