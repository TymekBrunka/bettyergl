cmake_minimum_required(VERSION 3.23)
project(betterGL LANGUAGES CXX C)

include(deps/ext.cmake)

add_library(glad src/glad/src/glad.c)
target_include_directories(glad PUBLIC src/glad/include)

add_library(stbimage src/stb/stb_image.c)
target_include_directories(stbimage PUBLIC src/stb/)

add_library(betterGL
  src/Debugging.cpp
  src/Program.cpp
  src/Assets.cpp
)

add_executable(imgPack src/assetPackers/imagePacker.cpp)
target_include_directories(imgPack PUBLIC src/include)
target_link_libraries(imgPack PRIVATE stbimage)

add_executable(bytePack src/assetPackers/bytePacker.cpp)
target_include_directories(bytePack PUBLIC src/include)

include(src/assetPackers/assetPackers.cmake)

target_include_directories(betterGL PUBLIC src/include)
target_link_libraries(betterGL glad stbimage)
target_compile_features(betterGL PUBLIC cxx_std_20)

option(BETTERGL_BUILD_TEST_EXAMPLE "" ON)
if (BETTERGL_BUILD_TEST_EXAMPLE)
  add_subdirectory(test_example)
endif()
