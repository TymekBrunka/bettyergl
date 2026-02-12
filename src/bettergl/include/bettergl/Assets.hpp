#pragma once
#include <string>
#include <type_traits>
namespace bgl {

struct Texture2DInfo {
  int width;
  int height;
  int nrOfChannels;
  unsigned char *data;
};

std::string readFile(const char *filepath);

Texture2DInfo loadImage(const char *filepath, int nrOfChannels = 0);

// image resource dispatcher - will load image from file if filepath is
// specified, otherwise it is assumed that provided resource contains data
template <const char *filepath = 0>
Texture2DInfo &getImgSrc(Texture2DInfo &resource) {
  if (filepath) {
    resource = loadImage(filepath);
  }
  return resource;
}

} // namespace bgl
