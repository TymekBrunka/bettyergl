#include <bettergl/Assets.hpp>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <stb_image.h>
#include <iostream>
namespace bgl {

std::string readFile(const char *filepath) {
  std::fstream file;
  file.open(filepath);
  file.seekg(0, std::ios::end);
  size_t length = file.tellg();
  file.seekg(0, std::ios::beg);

  const char *data_ = (const char *)calloc(1, length);
  std::string data(data_, length);
  file.read(data.data(), length);
  file.close();

  std::cout << data << "\n";

  return data;
}

Texture2DInfo loadImage(const char *filepath,
                                         int nrOfChannels_) {
  int width, height, nrOfChannels;
  unsigned char *data =
      stbi_load(filepath, &width, &height, &nrOfChannels, nrOfChannels_);
  return {.width = width, .height = height, .nrOfChannels = nrOfChannels};
}

} // namespace bgl
