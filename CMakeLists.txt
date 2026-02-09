cmake_minimum_required(VERSION 3.12)
project(betterGL LANGUAGES CXX C)

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

find_package(glfw3 REQUIRED)

add_subdirectory(src/bettergl)

add_executable(main src/main.cpp)
target_link_libraries(main glad glfw betterGL)
