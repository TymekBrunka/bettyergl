cmake_minimum_required(VERSION 3.23)
project(betterGL
  LANGUAGES CXX C
  VERSION 0.0.5
)
include(deps/ext.cmake)

# -- options
option(BETTERGL_BUILD_TEST_EXAMPLE "" ON)
option(BETTERGL_BUILD_STATIC "" ON)
option(BETTERGL_BUILD_DYNAMIC "" ON)
option(BETTERGL_CUSTOM_GLAD4 "custom glad target - updating requires rebuilding the library" OFF)
# -- options

if (NOT BETTERGL_CUSTOM_GLAD4 STREQUAL OFF)
  target(bettergl_glad ALIAS ${BETTERGL_CUSTOM_GLAD4})
else()
  add_library(bettergl_glad OBJECT src/glad/src/glad.c)
  target_link_options(bettergl_glad PRIVATE -fPIC)
  target_compile_options(bettergl_glad PRIVATE -fPIC)
  target_include_directories(bettergl_glad PUBLIC src/glad/include)
endif()

add_library(bettergl_stbimage OBJECT src/stb/stb_image.c)
target_compile_options(bettergl_stbimage PRIVATE -fPIC)
target_link_options(bettergl_stbimage PRIVATE -fPIC)
target_include_directories(bettergl_stbimage PUBLIC src/stb/)

add_executable(bettergl_imgPack src/assetPackers/imagePacker.cpp)
# target_include_directories(imgPack PUBLIC src/include)
target_link_libraries(bettergl_imgPack PRIVATE bettergl_stbimage)

add_executable(bettergl_bytePack src/assetPackers/bytePacker.cpp)
# target_include_directories(bytePack PUBLIC src/include)

include(src/assetPackers/assetPackers.cmake)

if (BETTERGL_BUILD_STATIC)
  add_library(betterGL_static STATIC
    src/Debugging.cpp
    src/Program.cpp
    src/Assets.cpp
  )
  target_include_directories(betterGL_static PUBLIC src/include)
  target_link_libraries(betterGL_static bettergl_glad bettergl_stbimage)
  target_compile_features(betterGL_static PUBLIC cxx_std_20)
endif()

if (BETTERGL_BUILD_DYNAMIC)
  add_library(betterGL_dynamic SHARED
    src/Debugging.cpp
    src/Program.cpp
    src/Assets.cpp
  )
  # target_compile_options(betterGL_dynamic PRIVATE -fPIC)
  target_include_directories(betterGL_dynamic PUBLIC src/include)
  target_link_libraries(betterGL_dynamic bettergl_glad bettergl_stbimage)
  target_compile_features(betterGL_dynamic PUBLIC cxx_std_20)
endif()

function(bettergl_copy_library)
  if (BETTERGL_BUILD_DYNAMIC)
    add_custom_command(
      TARGET betterGL_dynamic POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy 
        $<TARGET_FILE:betterGL_dynamic>
        # $<TARGET_FILE_DIR:betterGL_dynamic>
        ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE:betterGL_dynamic>
    )
  endif()
endfunction()

bettergl_copy_library(~/gex)

if (BETTERGL_BUILD_TEST_EXAMPLE)
  message("bettergl building test example")
  add_subdirectory(test_example)
endif()
