#include "Image.hpp"
#include <HardwareSerial.h>
#include <algorithm>
#include <cmath>
#include <vector>

Image::Image() {
  width = 0;
  height = 0;
  pixels = std::vector<Pixel>();
}

Image::Image(int width, int height) {
  this->width = width;
  this->height = height;
  pixels = std::vector<Pixel>(width * height);
}

Image Image::fromCamera(camera_fb_t *fb) {
  Image image = Image(fb->width, fb->height);
  Serial.println("Image width: " + String(image.width));
  Serial.println("Image height: " + String(image.height));

  for (int i = 0; i < image.height; i++) {
    for (int j = 0; j < image.width; j++) {
      int index = i * image.width + j;
      uint16_t pixel = ((uint16_t *)fb->buf)[index];
      uint8_t r = ((pixel & 0xF800) >> 11) * 255 / 31;
      uint8_t g = ((pixel & 0x07E0) >> 5) * 255 / 63;
      uint8_t b = (pixel & 0x001F) * 255 / 31;
      image.setPixel(j, i, Pixel(r, g, b));
    }
  }

  return image;
}

String Image::toString() {
  String result = "";
  if (!result.reserve(height * (width * 12 + 1))) {
    Serial.println("Failed to reserve memory for image string");
    return result;
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      Pixel pixel = getPixel(j, i);
      result +=
          String(pixel.r) + "," + String(pixel.g) + "," + String(pixel.b) + ";";
    }
    result += "\n";
  }
  return result;
}

Pixel Image::getPixel(int x, int y) const { return pixels[y * width + x]; }
void Image::setPixel(int x, int y, Pixel pixel) {
  pixels[y * width + x] = pixel;
}