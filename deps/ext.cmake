include(deps/deps_helper.cmake)

message("-- glfw 3.4")
find_package(glfw3 3.4 QUIET)
if (NOT glfw3_FOUND)
  ExternalProject_Add(
    glfw3
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
    CMAKE_ARGS
      "--install-prefix=${CM_INSTALL_DIR}"
      "-DGLFW_BUILD_EXAMPLES=OFF"
      "-DGLFW_BUILD_TESTS=OFF"
      "-DGLFW_BUILD_DOCS=OFF"
    CONFIGURE_HANDLED_BY_BUILD ON
    PREFIX ${CM_DOWNLOAD_DIR}
    INSTALL_DIR "${CM_INSTALL_DIR}"
  )
endif()

message("-- glew 2.3.1")
find_package(glew QUIET)
if (NOT glew_FOUND)
  ExternalProject_Add(
    glew
    URL "https://github.com/nigels-com/glew/releases/download/glew-2.3.1/glew-2.3.1.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE

    CONFIGURE_COMMAND "${CMAKE_COMMAND}" "-S" "${CM_DOWNLOAD_DIR}/src/glew/build/cmake" "-B" "${CM_DOWNLOAD_DIR}/src/glew-build" "--install-prefix=${CM_INSTALL_DIR}"
    BUILD_COMMAND "${CMAKE_COMMAND}" "--build" "${CM_DOWNLOAD_DIR}/src/glew-build"
      # "--install-prefix=${CM_INSTALL_DIR}"
    # SOURCE_DIR "${CM_DOWNLOAD_DIR}/src/glew/build/cmake"
    CONFIGURE_HANDLED_BY_BUILD ON
    PREFIX ${CM_DOWNLOAD_DIR}
    INSTALL_DIR "${CM_INSTALL_DIR}"
  )
endif()
