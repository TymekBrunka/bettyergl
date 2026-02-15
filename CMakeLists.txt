cmake_minimum_required(VERSION 3.12)
project(betterGL LANGUAGES CXX C)
include(deps/ext.cmake)

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

add_subdirectory(src/bettergl)

betterGL_bytepack(vertex src/shaders/vertex.glsl vertex.glsl d)
betterGL_bytepack(fragment src/shaders/fragment.glsl fragment.glsl d)

add_executable(main src/main.cpp)
# add_executable(main src/opengl_triangle.cpp)
target_link_libraries(main glad glfw betterGL vertex)
