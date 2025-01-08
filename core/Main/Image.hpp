#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "WString.h"
#include "esp_camera.h"
#include <Print.h>
#include <vector>

struct Pixel {
  uint8_t r;
  uint8_t g;
  uint8_t b;

  Pixel();
  Pixel(uint8_t r, uint8_t g, uint8_t b);
  Pixel(uint16_t rgb565);
  String toHexString() const;
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