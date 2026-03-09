#pragma once
#include <string>
namespace bgl {

struct Texture2DInfo loadImage(const char *filepath, int nrOfChannels = 0);

std::string readFile(const char *filepath);

struct Texture2DInfo {
  int width;
  int height;
  int nrOfChannels;
  unsigned char *data;

  const char *resPath;

  Texture2DInfo &getRes();
  void delRes();
};

struct dispatchedString {
  std::string data;

  const char *resPath;
  std::string &getRes();

  void delRes();
};

} // namespace bgl
