#include <bettergl/Assets.hpp>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <stb_image.h>
namespace bgl {

std::string readFile(const char *filepath) {
  std::fstream file;
  file.open(filepath);
  file.seekg(0, std::ios::end);
  int length = file.tellg();
  file.seekg(0, std::ios::beg);

  char *data_ = (char *)std::calloc(1, length);
  file.read(data_, length);
  file.close();

  std::string data(data_, length);
  return data;
}

Texture2DInfo loadImage(const char *filepath, int nrOfChannels_) {
  int width, height, nrOfChannels;
  unsigned char *data =
      stbi_load(filepath, &width, &height, &nrOfChannels, nrOfChannels_);
  return {.width = width, .height = height, .nrOfChannels = nrOfChannels};
}

Texture2DInfo &Texture2DInfo::getRes() {
  if (resPath) {
    Texture2DInfo info = loadImage(resPath);
    width = info.width;
    height = info.height;
    nrOfChannels = info.nrOfChannels;
    data = info.data;
  }

  return *this;
}

void Texture2DInfo::delRes() {
  if (resPath)
    free(data);
}

std::string &dispatchedString::getRes() {
  if (resPath)
    data = std::move(readFile(resPath));
  return data;
}

void dispatchedString::delRes() {
  if (resPath)
    delete &data;
}

} // namespace bgl
