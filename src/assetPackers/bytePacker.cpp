#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  const char *varname = argv[1];
  const char *input = argv[2];
  std::string output(argv[3]);
  const char build_mode = *argv[4];

  if (build_mode == 'd')
    std::cout << " +-----------Byte packer-----------\n"
              << " | input file:  \x1b[36m" << input << "\x1b[0m\n"
              << " | output file: \x1b[36m" << output << "\x1b[0m\n"
              << " +---------------------------------\n";

  std::string headerpath = output + ".hpp";
  std::string cppath = output + ".cpp";

#ifdef _WIN32
  size_t pos = headerpath.find("/");
  while (pos != std::string::npos) {
    headerpath.replace(pos, 1, "\\");
    pos = headerpath.find("/", pos + 2);
  }

  pos = cppath.find("/");
  while (pos != std::string::npos) {
    cppath.replace(pos, 1, "\\");
    pos = cppath.find("/", pos + 2);
  }
#endif

  std::FILE *header = std::fopen(headerpath.c_str(), "w");
  std::fprintf(header, "#pragma once\n"
                       "#include <bettergl/Assets.hpp>\n\n");

  if (build_mode == 'd')
    std::fprintf(header,
                 "#ifndef NDEBUG\n"
                 "inline bgl::dispatchedString %s = {std::string{}, \"%s\"};\n"
                 "#else\n"
                 "extern bgl::dispatchedString %s;\n"
                 "#endif",
                 varname, input, varname);
  else
    std::fprintf(header, "extern bgl::dispatchedString %s;\n", varname);
  std::fclose(header);

  if (build_mode == 'd') {
    std::FILE *file = std::fopen(cppath.c_str(), "w");
    std::fclose(file);
  }

  if (build_mode == 'r') {
    std::fstream f;
    f.open(input);
    f.seekg(0, std::ios::end);
    int length = f.tellg();
    f.seekg(0, std::ios::beg);
    char *data = (char *)std::calloc(length, sizeof(char));

    f.read(data, length);
    f.close();

    std::cout << " +-----------Byte packer-----------\n"
              << " | input file:  \x1b[36m" << input << "\x1b[0m\n"
              << " | output file: \x1b[36m" << output << "\x1b[0m\n"
              << " | byte length: \x1b[35m" << length << "\x1b[0m\n"
              << " +---------------------------------\n";

    char *sb = new char[length * 4];
    char *data_end = &data[length - 1];
    char *sbptr = sb;
    for (char *ptr = data; ptr < data_end; ptr++) {
      snprintf(sbptr, 5, "\\x%0.2x", *ptr);
      sbptr += 4;
    }

    std::FILE *cppfile = std::fopen(cppath.c_str(), "w");
    std::fprintf(cppfile,
                 "#include \"%s\"\n"
                 "#include <bettergl/Assets.hpp>\n"
                 "bgl::dispatchedString %s = {\"%s\", 0};",
                 headerpath.c_str(), varname, sb);
    std::fclose(cppfile);
    free(data);
    delete[] sb;
  }
}
