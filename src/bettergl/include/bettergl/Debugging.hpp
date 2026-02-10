#pragma once
#include <glad/glad.h>
#include <iostream>
#include <source_location>
#include <vector>
namespace bgl {

extern std::vector<const char*> SCOPE;
extern bool OPENGL_CORE_DBG_SUPPORT;

bool setUpDebugger();

void labelObject(GLenum type, GLuint object, const char *label,
                 GLsizei label_lenght = -1);
void beginDebugGroup(GLuint message_id, const char* name, GLsizei name_length = -1);
void endDebugGroup();

// glGetError wrapper that prints error enum to the stdout with current source
// location will be disabled in release mode unless BGL_CATCHERROR_ON_REL is
// defined
template <bool i = 0>
void catchError(const char *call_description = 0,
                std::source_location l =
                    std::source_location::current()) { // why is NULL in stddef

// turn off this function on release builds unless explicitly specified not to
#if !defined(NDEBUG) || defined(BGL_CATCHERROR_ON_REL)

  GLenum error_ = glGetError();
  if (error_ == GL_NO_ERROR)
    return;

  const char *error = "";
  switch (error_) {
  case GL_INVALID_ENUM:
    error = "GL_INVALID_ENUM";
    break;
  case GL_INVALID_VALUE:
    error = "GL_INVALID_VALUE";
    break;
  case GL_INVALID_OPERATION:
    error = "GL_INVALID_OPERATION";
    break;
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    error = "GL_INVALID_FRAMEBUFFER_OPERATION";
    break;
  case GL_OUT_OF_MEMORY:
    error = "GL_OUT_OF_MEMORY";
    break;
  case GL_STACK_OVERFLOW:
    error = "GL_STACK_OVERFLOW";
    break;
  case GL_STACK_UNDERFLOW:
    error = "GL_STACK_UNDERFLOW";
    break;
  default:
    error = "unknown";
    break;
  }

  std::cout << "\x1b[31mE\x1b[0m OpenGL \x1b[31m" << error
            << " \x1b[32m[\x1b[33m" << SCOPE.back();
  if (call_description) {
    std::cout << ".\x1b[34m" << call_description;
  }
  std::cout << "\x1b[32m]\x1b[0m at \x1b[33m" << l.file_name()
            << "\x1b[31m:" << l.line() << ":" << l.column() << "\x1b[0m\n";

#endif
}

} // namespace bgl
