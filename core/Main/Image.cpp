#include "Image.hpp"
#include <HardwareSerial.h>
#include <algorithm>
#include <cmath>
#include <vector>

Image Image::fromCamera(camera_fb_t *fb) {
  Image image;
  image.width = fb->width;
  image.height = fb->height;
  image.pixels = (int *)malloc(fb->width * fb->height * sizeof(int));

  for (int i = 0; i < fb->height; i++) {
    for (int j = 0; j < fb->width; j++) {
      image.pixels[i * fb->width + j] = fb->buf[i * fb->width + j];
    }
  }

  return image;
}

void Image::applyContourFilter() {
  int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  int *newPixels = new int[width * height];

  for (int y = 1; y < height - 1; ++y) {
    for (int x = 1; x < width - 1; ++x) {
      int sumX = 0;
      int sumY = 0;

      for (int ky = -1; ky <= 1; ++ky) {
        for (int kx = -1; kx <= 1; ++kx) {
          int pixelVal = pixels[(y + ky) * width + (x + kx)];
          sumX += pixelVal * Gx[ky + 1][kx + 1];
          sumY += pixelVal * Gy[ky + 1][kx + 1];
        }
      }

      int gradientMagnitude = std::sqrt(sumX * sumX + sumY * sumY);
      newPixels[y * width + x] = gradientMagnitude > 220 ? 255 : 0;
    }
  }

  for (int i = 0; i < width; ++i) {
    newPixels[i] = 0;
    newPixels[(height - 1) * width + i] = 0;
  }

  for (int i = 0; i < height; ++i) {
    newPixels[i * width] = 0;
    newPixels[i * width + width - 1] = 0;
  }

  for (int i = 0; i < width * height; ++i) {
    pixels[i] = newPixels[i];
  }

  delete[] newPixels;
}

struct Line {
  double rho;
  double theta;
};

String Image::toString() {
  String result = "";
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      result += String(pixels[i * this->width + j]) + " ";
    }
    result += "\n";
  }

  return result;
}

int Image::getPixel(int x, int y) const { return pixels[y * width + x]; }