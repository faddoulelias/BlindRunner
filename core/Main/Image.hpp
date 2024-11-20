#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "WString.h"
#include "esp_camera.h"

class Image {
public:
  String toString();
  static Image fromCamera(camera_fb_t *fb);
  void applyContourFilter();
  int getPixel(int x, int y) const;

private:
  int width;
  int height;
  int *pixels;
};

#endif