cmake_minimum_required(VERSION 3.23)
project(betterGL LANGUAGES CXX C)

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

add_library(stbimage stb/stb_image.c)
target_include_directories(stbimage PUBLIC stb/)

add_library(betterGL
  Debugging.cpp
  Program.cpp
  Assets.cpp
)

add_executable(imgPack assetPackers/imagePacker.cpp)
target_include_directories(imgPack PUBLIC include)
target_link_libraries(imgPack PRIVATE stbimage)

add_executable(bytePack assetPackers/bytePacker.cpp)
target_include_directories(bytePack PUBLIC include)

include(assetPackers/assetPackers.cmake)

target_include_directories(betterGL PUBLIC include)
target_link_libraries(betterGL glad stbimage)
target_compile_features(betterGL PUBLIC cxx_std_20)
