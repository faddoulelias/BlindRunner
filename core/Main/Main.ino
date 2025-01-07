#include "Camera.hpp"
#include "DFRobot_AXP313A.h"
#include <HTTPClient.h>
#include <WiFi.h>

const char *ssid = "Pixel_1913";
const char *password = "221143LB";

const char *serverName = "http://192.168.69.197:5000/update";
HTTPClient http;

void sendPhoto() {
  http.begin(serverName);
  http.addHeader("Content-Type", "text/plain");
  Image image = Camera.capture();
  int httpResponseCode = http.POST(image.toString());
  Serial.printf("HTTP Response code: %d\n", httpResponseCode);
  http.end();
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.setDebugOutput(true);

  if (psramInit()) {
    Serial.println("PSRAM initialized successfully");
  } else {
    Serial.println("PSRAM initialization failed");
    return;
  }

  Serial.println("Setting up camera...");
  Camera.setup();
  Serial.println("Camera setup complete");

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Setup complete");
}

void loop() {
  Serial.println("Taking photo...");
  sendPhoto();
  delay(100);
}