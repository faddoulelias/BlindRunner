#include "Camera.hpp"
#include "DFRobot_AXP313A.h"
#include <HTTPClient.h>

#include <WiFi.h>

const char *ssid = "******";
const char *password = "******";

const char *serverName = "http://192.168.172.197:5000/update";
HTTPClient http;

void sendPhoto() {
  http.addHeader("Content-Type", "text/plain");
  Image image = Camera.capture();
  image.applyContourFilter();

  int httpResponseCode = http.POST(image.toString());
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  Camera.setup();

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  http.begin(serverName);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("Camera Ready!");
  Serial.print(WiFi.localIP());
}

void loop() {
  Serial.print("Taking photo");
  sendPhoto();
}