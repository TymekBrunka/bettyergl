cmake_minimum_required(VERSION 3.23)
project(betterGL
  LANGUAGES CXX C
  VERSION 0.0.1
)

include(deps/ext.cmake)
find_package(glew CONFIG)

add_library(bettergl_stbimage src/stb/stb_image.c)
target_include_directories(bettergl_stbimage PUBLIC src/stb/)

add_library(betterGL
  src/Debugging.cpp
  src/Program.cpp
  src/Assets.cpp
)

add_executable(bettergl_imgPack src/assetPackers/imagePacker.cpp)
# target_include_directories(imgPack PUBLIC src/include)
target_link_libraries(bettergl_imgPack PRIVATE bettergl_stbimage)

add_executable(bettergl_bytePack src/assetPackers/bytePacker.cpp)
# target_include_directories(bytePack PUBLIC src/include)

include(src/assetPackers/assetPackers.cmake)

target_include_directories(betterGL PUBLIC src/include)
target_link_libraries(betterGL PRIVATE bettergl_stbimage GLEW::GLEW)
target_compile_features(betterGL PUBLIC cxx_std_20)

option(BETTERGL_BUILD_TEST_EXAMPLE "" ON)
if (BETTERGL_BUILD_TEST_EXAMPLE)
  add_subdirectory(test_example)
endif()
