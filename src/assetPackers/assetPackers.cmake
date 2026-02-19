function(byterGL_imgpack name input output flip channels build_mode)
  message("Image packing ${name}")
  if( build_mode STREQUAL "d")
    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/${output}.hpp ${CMAKE_BINARY_DIR}/${output}.cpp
      COMMAND imgpack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${CMAKE_BINARY_DIR}/${output} ${channels} ${flip} d

      DEPENDS imgpacker
      VERBATIM
    )
  else()
    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/${output}.hpp ${CMAKE_BINARY_DIR}/${output}.cpp
      COMMAND imgpack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${CMAKE_BINARY_DIR}/${output} ${channels} ${flip} r

      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${input} imgpacker
      VERBATIM
    )
  endif()
	add_custom_target(${name}_file DEPENDS ${CMAKE_BINARY_DIR}/${output}.cpp)
	add_library(${name} STATIC ${CMAKE_BINARY_DIR}/${output}.cpp)
	add_dependencies(${name} ${name}_file)
	target_link_libraries(${name} glad stb_image)
  message(${BETTERGL_ROOT_DIR})
  target_include_directories(${name} PUBLIC ${betterGL_SOURCE_DIR}/include/ ${CMAKE_BINARY_DIR})

endfunction()

function(betterGL_bytepack name input output build_mode)
  message("Byte packing ${name}")
  if( build_mode STREQUAL "d")
    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/${output}.hpp ${CMAKE_BINARY_DIR}/${output}.cpp
      COMMAND bytePack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${CMAKE_BINARY_DIR}/${output} d

      DEPENDS bytePack
      VERBATIM
    )
  else()
    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/${output}.hpp ${CMAKE_BINARY_DIR}/${output}.cpp
      COMMAND bytePack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${CMAKE_BINARY_DIR}/${output} r

      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${input} bytePack
      VERBATIM
    )
  endif()
	add_custom_target(${name}_file DEPENDS ${CMAKE_BINARY_DIR}/${output}.cpp)
	add_library(${name} STATIC ${CMAKE_BINARY_DIR}/${output}.cpp)
	add_dependencies(${name} ${name}_file)
  target_include_directories(${name} PUBLIC ${betterGL_SOURCE_DIR}/include/ ${CMAKE_BINARY_DIR})

endfunction()
