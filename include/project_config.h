#pragma once

#include <Arduino.h>

// NodeMCU / ESP8266 pin mapping.
static const uint8_t IR_PINS[4] = {D5, D6, D7, D0};
static const uint8_t I2C_SDA_PIN = D2;
static const uint8_t I2C_SCL_PIN = D1;

// Most common digital IR modules assert LOW when an object is detected.
// Change to HIGH if your particular sensor module behaves differently.
#ifndef SENSOR_ACTIVE_LEVEL
#define SENSOR_ACTIVE_LEVEL LOW
#endif

#ifndef OLED_I2C_ADDRESS
#define OLED_I2C_ADDRESS 0x3C
#endif
#ifndef PCF8574_I2C_ADDRESS
#define PCF8574_I2C_ADDRESS 0x20
#endif

#ifndef MQTT_TOPIC
#define MQTT_TOPIC "parking/site-a/status"
#endif
#ifndef MQTT_DEVICE_ID
#define MQTT_DEVICE_ID "smart-parking-01"
#endif
#ifndef MQTT_INTERVAL_MS
#define MQTT_INTERVAL_MS 15000UL
#endif
