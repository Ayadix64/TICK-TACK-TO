cmake_minimum_required(VERSION 3.16)
project(ticktackto)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug) #remeber to delet this if you want a user app, this increase the app length to better debug

find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)

add_library(ticktackto src/core.c src/utils.c src/basics.c src/render.c src/text.c src/ui.c)

# im gui  externel/imgui/imgui.cpp externel/imgui/imgui_demo.cpp externel/imgui/imgui_draw.cpp externel/imgui/imgui_tables.cpp externel/imgui/imgui_widgets.cpp externel/imgui/imgui_impl_glfw.cpp externel/imgui/imgui_impl_opengl3.cpp 

include_directories(include/)


target_link_libraries(ticktackto glfw3)


if (install)
    install(TARGETS ticktackto
            EXPORT ticktacktoTargets
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()
project(demos)

