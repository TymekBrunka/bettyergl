cmake_minimum_required(VERSION 3.12)
project(bettergl_example LANGUAGES CXX C)

bettergl_copy_library()

betterGL_bytepack(vertex shaders/vertex.glsl vertex.glsl r)
betterGL_bytepack(fragment shaders/fragment.glsl fragment.glsl)

add_executable(main main.cpp)
# add_executable(main src/opengl_triangle.cpp)
target_link_libraries(main glfw betterGL_dynamic vertex fragment)
