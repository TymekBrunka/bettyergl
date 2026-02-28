function(byterGL_imgpack name input output flip channels)
  set(build_mode ${ARGV5})
  string(PREPEND output "${CMAKE_CURRENT_BINARY_DIR}/")
  message("Image packing ${name}")
  # if( build_mode STREQUAL "d")
  #   add_custom_command(
  #     OUTPUT ${output}.hpp ${output}.cpp
  #     COMMAND imgpack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${output} ${channels} ${flip} d
  #
  #     DEPENDS imgPack
  #     VERBATIM
  #   )
  # else()
  #   add_custom_command(
  #     OUTPUT ${output}.hpp ${output}.cpp
  #     COMMAND imgpack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${output} ${channels} ${flip} r
  #
  #     DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${input} imgPack
  #     VERBATIM
  #   )
  # endif()
  if (NOT build_mode)
    set(build_mode $<IF:$<CONFIG:Release>,r,d>)
    set(isreal $<CONFIG:Release>)
  endif()
  if (NOT build_mode STREQUAL r)
    set(build_mode d)
    set(isreal 0)
  endif()

  add_custom_command(
    OUTPUT ${output}.hpp ${output}.cpp
    COMMAND imgpack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${output} ${channels} ${flip} ${build_mode}

    DEPENDS $<IF:${isreal},${CMAKE_CURRENT_SOURCE_DIR}/${input},> imgPack
    VERBATIM
  )

  add_custom_target(${name}_file DEPENDS "${output}.cpp")
  add_library(${name} STATIC "${output}.cpp")
  add_dependencies(${name} ${name}_file)
  target_link_libraries(${name} glad stb_image)
  target_include_directories(${name} PUBLIC "${betterGL_SOURCE_DIR}/src/include/" ${CMAKE_CURRENT_BINARY_DIR})

endfunction()

function(betterGL_bytepack name input output)
  set(build_mode ${ARGV3})
  string(PREPEND output "${CMAKE_CURRENT_BINARY_DIR}/")
  message("Byte packing ${name}")
  # if( build_mode STREQUAL "d")
  #   add_custom_command(
  #     OUTPUT ${output}.hpp ${output}.cpp
  #     COMMAND bytePack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${output} d
  #
  #     DEPENDS bytePack
  #     VERBATIM
  #   )
  # else()
  #   add_custom_command(
  #     OUTPUT ${output}.hpp ${output}.cpp
  #     COMMAND bytePack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${output} r
  #
  #     DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${input} bytePack
  #     VERBATIM
  #   )
  # endif()

  set(isreal 0)
  if (NOT build_mode)
    set(build_mode $<IF:$<CONFIG:Release>,r,d>)
    set(isreal $<CONFIG:Release>)
  endif()
  if (NOT build_mode STREQUAL r)
    set(build_mode d)
    set(isreal 0)
  endif()

  add_custom_command(
    OUTPUT ${output}.hpp ${output}.cpp
    COMMAND bytePack ${name} ${CMAKE_CURRENT_SOURCE_DIR}/${input} ${output} ${build_mode}

    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${input} bytePack
    DEPENDS $<IF:${isreal},${CMAKE_CURRENT_SOURCE_DIR}/${input},> bytePack
    VERBATIM
  )

  add_custom_target(${name}_file DEPENDS "${output}.cpp")
  add_library(${name} STATIC "${output}.cpp")
  add_dependencies(${name} ${name}_file)
  target_include_directories(${name} PUBLIC "${betterGL_SOURCE_DIR}/src/include/" ${CMAKE_CURRENT_BINARY_DIR})

endfunction()
