#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "DFRobot_AXP313A.h"
#include "Image.hpp"
#include "esp_camera.h"

class CameraClass {
public:
  void setup();
  Image capture();

private:
  DFRobot_AXP313A axp;
};

extern CameraClass Camera;

#endif