#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include "project_config.h"

#ifndef MQTT_ENABLED
#define MQTT_ENABLED 0
#endif

#if MQTT_ENABLED
  #include <PubSubClient.h>
  #if __has_include("secrets.h")
    #include "secrets.h"
  #else
    #error "MQTT build requires include/secrets.h. Copy secrets.example.h and configure it locally."
  #endif
  #ifndef MQTT_PORT
    #define MQTT_PORT 1883
  #endif
#endif

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool occupied[4] = {false, false, false, false};
bool previous[4] = {false, false, false, false};
bool displayReady = false;
uint32_t lastPublish = 0;

#if MQTT_ENABLED
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
#endif

// PCF8574 output map: P0..P3 green LEDs, P4..P7 red LEDs.
// A HIGH output is treated as indicator ON. Verify the actual module/driver wiring.
uint8_t makeLedMask() {
  uint8_t mask = 0;
  for (uint8_t i = 0; i < 4; ++i) {
    if (occupied[i]) mask |= (1U << (i + 4));
    else mask |= (1U << i);
  }
  return mask;
}

bool writePcf8574(uint8_t value) {
  Wire.beginTransmission(PCF8574_I2C_ADDRESS);
  Wire.write(value);
  return Wire.endTransmission() == 0;
}

void readSlots() {
  for (uint8_t i = 0; i < 4; ++i) {
    const int raw = digitalRead(IR_PINS[i]);
    occupied[i] = (raw == SENSOR_ACTIVE_LEVEL);
  }
}

uint8_t countOccupied() {
  uint8_t total = 0;
  for (bool state : occupied) if (state) ++total;
  return total;
}

void renderDisplay() {
  if (!displayReady) return;
  const uint8_t full = countOccupied();
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("SMART PARKING"));
  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);
  for (uint8_t i = 0; i < 4; ++i) {
    display.setCursor(0, 16 + (i * 10));
    display.print(F("Slot "));
    display.print(i + 1);
    display.print(F(": "));
    display.println(occupied[i] ? F("OCCUPIED") : F("VACANT"));
  }
  display.setCursor(0, 57);
  display.print(F("Free: "));
  display.print(4 - full);
  display.print(F(" / 4"));
  display.display();
}

#if MQTT_ENABLED
void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  const uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 12000UL) {
    delay(250);
    yield();
  }
}

void connectMqtt() {
  if (mqttClient.connected() || WiFi.status() != WL_CONNECTED) return;
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  String clientId = String(MQTT_DEVICE_ID) + "-" + String(ESP.getChipId(), HEX);
  if (strlen(MQTT_USER) > 0) mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD);
  else mqttClient.connect(clientId.c_str());
}

void publishStatus() {
  if (!mqttClient.connected()) return;
  String payload = "{\"device\":\"";
  payload += MQTT_DEVICE_ID;
  payload += "\",\"slots\":[";
  for (uint8_t i = 0; i < 4; ++i) {
    if (i) payload += ",";
    payload += "{\"slot\":";
    payload += String(i + 1);
    payload += ",\"occupied\":";
    payload += occupied[i] ? "true" : "false";
    payload += "}";
  }
  payload += "],\"available\":";
  payload += String(4 - countOccupied());
  payload += ",\"occupied\":";
  payload += String(countOccupied());
  payload += "}";
  mqttClient.publish(MQTT_TOPIC, payload.c_str(), true);
}
#endif

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0; i < 4; ++i) pinMode(IR_PINS[i], INPUT);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  displayReady = display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS);
  if (!displayReady) Serial.println(F("WARN: OLED not detected"));

  if (!writePcf8574(0x00)) Serial.println(F("WARN: PCF8574 not detected"));
  readSlots();
  renderDisplay();

#if MQTT_ENABLED
  connectWiFi();
  connectMqtt();
#endif
}

void loop() {
  readSlots();
  const bool changed = memcmp(occupied, previous, sizeof(occupied)) != 0;

  if (changed) {
    writePcf8574(makeLedMask());
    renderDisplay();
    memcpy(previous, occupied, sizeof(occupied));
    Serial.println(F("Parking occupancy changed"));
  }

  // Ensure indicators are initialized even when initial state is all vacant.
  static bool indicatorsInitialized = false;
  if (!indicatorsInitialized) {
    writePcf8574(makeLedMask());
    indicatorsInitialized = true;
  }

#if MQTT_ENABLED
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (!mqttClient.connected()) connectMqtt();
  mqttClient.loop();
  if (changed || millis() - lastPublish >= MQTT_INTERVAL_MS) {
    publishStatus();
    lastPublish = millis();
  }
#endif
  delay(250);
}
