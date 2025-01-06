#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "WString.h"
#include "esp_camera.h"

struct Pixel {
  int r;
  int g;
  int b;
};

class Image {
public:
  String toString();
  static Image fromCamera(camera_fb_t *fb);
  Pixel getPixel(int x, int y) const;

private:
  int width;
  int height;
  Pixel *pixels;
};

#endif