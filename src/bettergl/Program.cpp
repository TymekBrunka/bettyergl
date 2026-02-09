#include "bettergl/Debugging.hpp"
#include "bettergl/GLTypes.hpp"
#include <bettergl/Program.hpp>
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <string>
#include <string_view>
namespace bgl {

Result<Shader> createShader(GLenum shader_type, const char *source) {

  if (shader_type != GL_VERTEX_SHADER && shader_type != GL_FRAGMENT_SHADER &&
      shader_type != GL_GEOMETRY_SHADER) {
    return {0, std::string("shader creation error: invalid enum")};
  }

  Shader shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int compilation_status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_status);

  std::stringstream error_msg;
  if (!compilation_status) {
    const char *shader_type_s;

    switch (shader_type) {
    case GL_VERTEX_SHADER:
      shader_type_s = "vertex";
      break;
    case GL_FRAGMENT_SHADER:
      shader_type_s = "fragment";
      break;
    case GL_GEOMETRY_SHADER:
      shader_type_s = "geometry";
      break;
    }
    error_msg << shader_type_s << " shader linking error: ";
    std::string shader_error_msg;
    shader_error_msg.resize(512);
    glGetShaderInfoLog(shader, 512, NULL, shader_error_msg.data());
    std::cout << shader_error_msg << "\n";

    size_t separator_pos = shader_error_msg.find_first_of(':');
    if (separator_pos != -1) {
      do { // so we can break out
        // getting indexes needed to retrieve column in shader source
        size_t location_end_pos =
            shader_error_msg.find_first_of(':', separator_pos + 1);

        if (location_end_pos == -1)
          break;

        size_t potential_parentesis_pos = shader_error_msg.find_first_of('(');
        size_t column_index_end_pos = potential_parentesis_pos;
        if (potential_parentesis_pos == -1 ||
            potential_parentesis_pos > location_end_pos) {
          column_index_end_pos = location_end_pos;
        }

        std::cout << shader_error_msg.substr(0, column_index_end_pos) << "\n";

        size_t line = atoi(shader_error_msg.substr(0, separator_pos).c_str());
        size_t column = atoi(shader_error_msg.substr(separator_pos + 1, column_index_end_pos).c_str());

        size_t line_start_index = 0;
        for (size_t i = 0; i < line; i++) {
          line_start_index = shader_error_msg.find_first_of('\n', line_start_index) + 1;
        }

        std::cout << std::string_view(&source[line_start_index], &source[line_start_index + column]);

      } while (false);
    }
    glDeleteShader(shader);
  }

  return {shader, error_msg.str()};
}

Result<Program> linkProgram(Program program, const char *name) {
  glLinkProgram(program);
  int linking_status;
  glGetProgramiv(program, GL_LINK_STATUS, &linking_status);

  std::string error_msg;
  if (!linking_status) {
    std::string shader_type_s;

    error_msg = std::string("program '") + (name ? name : "") +
                std::string("' linking error: ");
    int msg_size = error_msg.size();
    error_msg.resize(590);
    glGetProgramInfoLog(program, 512, NULL, error_msg.data() + msg_size);
    glDeleteProgram(program);
  }

  return {program, error_msg};
}

// may not result program if shaders fail to compile
Result<Program> createProgram(const char *name,
                              const char *vertex_shader_source,
                              const char *fragment_shader_source) {

  Result<Shader> vertex_shader_ =
      createShader(GL_VERTEX_SHADER, vertex_shader_source);

  if (!vertex_shader_.error_msg.empty()) {
    vertex_shader_.error_msg =
        std::string("On program '") + name + "' " + vertex_shader_.error_msg;
    return vertex_shader_;
  }

  Result<Shader> fragment_shader_ =
      createShader(GL_FRAGMENT_SHADER, fragment_shader_source);

  if (!fragment_shader_.error_msg.empty()) {
    fragment_shader_.error_msg =
        std::string("On program '") + name + "' " + fragment_shader_.error_msg;
    return fragment_shader_;
  }

  Program program = glCreateProgram();
  glAttachShader(program, vertex_shader_.self);
  glAttachShader(program, fragment_shader_.self);

  return linkProgram(program, name);
}

} // namespace bgl
