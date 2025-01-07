#include "Camera.hpp"
#include "esp_heap_caps.h" // Include heap capabilities library
#include "esp_log.h"       // Include logging library

static const char *TAG = "CameraClass"; // Define a tag for logging

void CameraClass::setup() {
  if (!psramInit()) {
    ESP_LOGE(TAG, "PSRAM initialization failed");
    return;
  }

  // Log available PSRAM
  size_t free_psram = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
  ESP_LOGI(TAG, "Free PSRAM: %d bytes", free_psram);

  // Log available DRAM
  size_t free_dram = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  ESP_LOGI(TAG, "Free DRAM: %d bytes", free_dram);

  axp = DFRobot_AXP313A();
  const int PWDN_GPIO_NUM = -1;
  const int RESET_GPIO_NUM = -1;
  const int XCLK_GPIO_NUM = 45;
  const int SIOD_GPIO_NUM = 1;
  const int SIOC_GPIO_NUM = 2;
  const int Y9_GPIO_NUM = 48;
  const int Y8_GPIO_NUM = 46;
  const int Y7_GPIO_NUM = 8;
  const int Y6_GPIO_NUM = 7;
  const int Y5_GPIO_NUM = 4;
  const int Y4_GPIO_NUM = 41;
  const int Y3_GPIO_NUM = 40;
  const int Y2_GPIO_NUM = 39;
  const int VSYNC_GPIO_NUM = 6;
  const int HREF_GPIO_NUM = 42;
  const int PCLK_GPIO_NUM = 5;

  while (axp.begin() != 0) {
    ESP_LOGE(TAG, "AXP313A initialization failed, retrying...");
    delay(1000);
  }
  axp.enableCameraPower(axp.eOV2640);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_RGB565;
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.frame_size = FRAMESIZE_QQVGA;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Camera init failed with error 0x%x", err);
    return;
  }
  ESP_LOGI(TAG, "Camera initialized successfully");
}

Image CameraClass::capture() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    ESP_LOGE(TAG, "Camera capture failed");
    return Image(); // Return an empty image or handle error appropriately
  }
  Image image = Image::fromCamera(fb);
  esp_camera_fb_return(fb);

  return image;
}

CameraClass Camera;