cmake_minimum_required(VERSION 3.23)
project(betterGL
  LANGUAGES CXX C
  VERSION 0.0.2
)
include(deps/ext.cmake)

# -- options
option(BETTERGL_BUILD_TEST_EXAMPLE "" ON)
option(BETTERGL_CUSTOM_GLAD4 "custom glad target - updating requires rebuilding the library" OFF)
# -- options

if (NOT BETTERGL_CUSTOM_GLAD4 STREQUAL OFF)
  target(bettergl_glad ALIAS ${BETTERGL_CUSTOM_GLAD4})
else()
  add_library(bettergl_glad src/glad/src/glad.c)
  target_include_directories(bettergl_glad PUBLIC src/glad/include)
endif()

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
target_link_libraries(betterGL bettergl_glad bettergl_stbimage)
target_compile_features(betterGL PUBLIC cxx_std_20)

if (BETTERGL_BUILD_TEST_EXAMPLE STREQUAL ON)
  add_subdirectory(test_example)
endif()
