include(deps/deps_helper.cmake)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
  message("Ccache enabled")
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM} base_dir=${PROJECT_SOURCE_DIR} hash_dir=false)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM} base_dir=${PROJECT_SOURCE_DIR} hash_dir=false)
endif()


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
