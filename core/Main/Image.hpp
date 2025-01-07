#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "WString.h"
#include "esp_camera.h"
#include <vector>

struct Pixel {
  int r;
  int g;
  int b;

  Pixel() : r(0), g(0), b(0) {}
  Pixel(int r, int g, int b) : r(r), g(g), b(b) {}
};

class Image {
public:
  Image();
  Image(int width, int height);
  String toString();
  static Image fromCamera(camera_fb_t *fb);
  Pixel getPixel(int x, int y) const;
  void setPixel(int x, int y, Pixel pixel);

private:
  int width;
  int height;
  std::vector<Pixel> pixels;
};

#endif