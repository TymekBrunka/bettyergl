cmake_minimum_required(VERSION 3.23)
project(betterGL LANGUAGES CXX C)

add_library(stbimage stb/stb_image.c)
target_link_libraries(stbimage PUBLIC stb/)

add_library(betterGL
  Debugging.cpp
  Program.cpp
)
target_include_directories(betterGL PUBLIC include)
target_link_libraries(betterGL glad stbimage)
target_compile_features(betterGL PUBLIC cxx_std_20)
