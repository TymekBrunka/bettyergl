cmake_minimum_required(VERSION 3.12)
project(betterGL LANGUAGES CXX C)

betterGL_bytepack(vertex shaders/vertex.glsl vertex.glsl r)
betterGL_bytepack(fragment shaders/fragment.glsl fragment.glsl)

add_executable(main main.cpp)
# add_executable(main src/opengl_triangle.cpp)
target_link_libraries(main glad glfw betterGL vertex)
