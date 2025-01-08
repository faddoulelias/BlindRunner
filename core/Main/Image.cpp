#include "Image.hpp"
#include <HardwareSerial.h>
#include <algorithm>
#include <cmath>
#include <vector>

// ----------------------------------------------------------------------------
// IMAGE CLASS ----------------------------------------------------------------
// ----------------------------------------------------------------------------

Image::Image() : width(0), height(0), pixels() {}

Image::Image(int width, int height)
    : width(width), height(height), pixels(width * height) {}

Image Image::fromCamera(camera_fb_t *fb) {
  Image image = Image(fb->width, fb->height);

  uint16_t *fb_data = (uint16_t *)fb->buf;
  for (int i = 0; i < fb->height; i++) {
    for (int j = 0; j < fb->width; j++) {
      image.setPixel(j, i, Pixel(fb_data[i * fb->width + j]));
    }
  }

  return image;
}

String Image::toString() {
  String result;
  if (!result.reserve(height * (width * 8 + 1))) {
    Serial.println("Failed to reserve memory for image string");
    return result;
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      result += "#" + getPixel(j, i).toHexString() + " ";
    }
    result += "\n";
  }
  return result;
}

Pixel Image::getPixel(int x, int y) const { return pixels[y * width + x]; }

void Image::setPixel(int x, int y, Pixel pixel) {
  pixels[y * width + x] = pixel;
}

// ----------------------------------------------------------------------------
// PIXEL CLASS ----------------------------------------------------------------
// ----------------------------------------------------------------------------

Pixel::Pixel() : r(0), g(0), b(0) {}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

Pixel::Pixel(uint16_t rgb565) {
  rgb565 = (rgb565 >> 8) | (rgb565 << 8);
  r = ((rgb565 >> 11) & 0x1F) * 255 / 31;
  g = ((rgb565 >> 5) & 0x3F) * 255 / 63;
  b = (rgb565 & 0x1F) * 255 / 31;
}

String Pixel::toHexString() const {
  char hex[7];
  snprintf(hex, sizeof(hex), "%02X%02X%02X", r, g, b);
  return String(hex);
}
