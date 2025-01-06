#include "Image.hpp"
#include <HardwareSerial.h>
#include <algorithm>
#include <cmath>
#include <vector>

Image Image::fromCamera(camera_fb_t *fb) {
  Image image;
  image.width = fb->width;
  image.height = fb->height;
  Serial.println(image.width, image.height);
  image.pixels = (Pixel *)malloc(image.width * image.height * sizeof(Pixel));

  for (int i = 0; i < image.height; i++) {
    for (int j = 0; j < image.width; j++) {
      int index = i * image.width + j;
      image.pixels[index].r = fb->buf[index * 3];
      image.pixels[index].g = fb->buf[index * 3 + 1];
      image.pixels[index].b = fb->buf[index * 3 + 2];
    }
  }

  return image;
}

String Image::toString() {
  String result = "";
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int index = i * width + j;
      result += String(pixels[index].r) + "," + String(pixels[index].g) + "," +
                String(pixels[index].b) + ";";
    }
    result += "\n";
  }

  return result;
}

Pixel Image::getPixel(int x, int y) const { return pixels[y * width + x]; }