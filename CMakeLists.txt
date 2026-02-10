cmake_minimum_required(VERSION 3.12)
project(betterGL LANGUAGES CXX C)
include(deps/ext.cmake)

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

add_subdirectory(src/bettergl)

add_executable(main src/main.cpp)
target_link_libraries(main glad glfw betterGL)
