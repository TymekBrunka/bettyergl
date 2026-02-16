#include <bettergl/Debugging.hpp>
namespace bgl {

std::vector<const char *> SCOPE;
bool OPENGL_CORE_DBG_SUPPORT = false;

inline void APIENTRY GLDEBUGFUNC(GLenum source_, GLenum type_, GLuint id,
                                 GLenum severity_, GLsizei length,
                                 const GLchar *message, const void *userParam) {
  switch (id) {
  case 131185: // glBufferData
    return;
  }

  const char *type;
  const char *severity;
  const char *source;

  switch (type_) {
  case GL_DEBUG_TYPE_ERROR_ARB:
    type = "\x1b[31mE\x1b[0m";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
    type = "\x1b[33mDB\x1b[0m";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
    type = "\x1b[31mUB\x1b[0m";
    break;
  case GL_DEBUG_TYPE_PORTABILITY_ARB:
    type = "\x1b[34mPORT\x1b[0m";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE_ARB:
    type = "\x1b[34mPERF\x1b[0m";
    break;
  case GL_DEBUG_TYPE_MARKER_KHR:
    type = "\x1b[35mMARK\x1b[0m";
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP_KHR:
    type = "\x1b[35mPUSH\x1b[0m";
    break;
  case GL_DEBUG_TYPE_POP_GROUP_KHR:
    type = "\x1b[35mPOP\x1b[0m";
    break;
  case GL_DEBUG_TYPE_OTHER_ARB:
    type = "OTHER";
    break;
  }

  switch (severity_) {
  case GL_DEBUG_SEVERITY_LOW_ARB:
    severity = "\x1b[34mL\x1b[0m";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM_ARB:
    severity = "\x1b[33mM\x1b[0m";
    break;
  case GL_DEBUG_SEVERITY_HIGH_ARB:
    severity = "\x1b[31mH\x1b[0m";
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION_KHR:
    severity = "\x1b[35mN\x1b[0m";
    break;
  }

  switch (source_) {
  case GL_DEBUG_SOURCE_API_ARB:
    source = "API";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
    source = "Window System";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
    source = "Shader Compiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
    source = "Third Party";
    break;
  case GL_DEBUG_SOURCE_APPLICATION_ARB:
    source = "Application";
    break;
  case GL_DEBUG_SOURCE_OTHER_ARB:
    source = "Other";
    break;
  }

  std::cout << type << "/" << severity << " \x1b[32m[\x1b[33m"
            << (SCOPE.size() > 0 ? SCOPE.back() : "")
            << "\x1b[32m]\x1b[0m OpenGL source: \x1b[33m" << source
            << "\x1b[0m message: " << message << "\n";
}

bool setUpDebugger() {
  if (OPENGL_CORE_DBG_SUPPORT) {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDEBUGFUNC, NULL);
  } else if (GLAD_GL_ARB_debug_output || GLAD_GL_KHR_debug) {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    glDebugMessageCallbackARB(GLDEBUGFUNC, NULL);
    return true;
  }
  return false;
}

void labelObject(GLenum type, GLuint object, const char *label,
                 GLsizei label_lenght) {
  if (OPENGL_CORE_DBG_SUPPORT)
    glObjectLabel(type, object, label_lenght, label);
  else if (GLAD_GL_KHR_debug || GLAD_GL_EXT_debug_label) {
    glObjectLabelKHR(type, object, label_lenght, label);
    catchError();
  }
}

void beginDebugGroup(GLuint message_id, const char *name, GLsizei name_length) {
  SCOPE.push_back(name);
  if (OPENGL_CORE_DBG_SUPPORT)
    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, message_id, name_length,
                     name);
  else if (GLAD_GL_KHR_debug)
    glPushDebugGroupKHR(GL_DEBUG_SOURCE_APPLICATION_KHR, message_id,
                        name_length, name);
}

void endDebugGroup() {
  if (SCOPE.size() > 0)
    SCOPE.pop_back();
  if (OPENGL_CORE_DBG_SUPPORT)
    glPopDebugGroup();
  else if (GLAD_GL_KHR_debug)
    glPopDebugGroupKHR();
}

#ifndef BGL_REL_NO_LTO
template void catchError<>(const char *call_description,
                           std::source_location l);
#endif
} // namespace bgl
