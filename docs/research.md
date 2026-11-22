# Technical Research and Design Rationale

This project combines low-cost digital sensing, an ESP8266 Wi-Fi microcontroller, an I2C display, an I/O expander and optional MQTT messaging.

## Design rationale
- **ESP8266:** provides a compact microcontroller platform with integrated Wi-Fi suitable for an educational connected-device prototype.
- **Digital IR obstacle sensors:** simple binary detection can demonstrate per-slot occupancy. Their output depends on module adjustment, target reflectivity, distance and ambient light; calibration is essential.
- **SSD1306 OLED:** compact I2C display allows local status feedback without a separate display controller.
- **PCF8574:** adds eight quasi-bidirectional I/O lines over I2C, reducing the number of ESP8266 GPIO pins needed for eight indicators.
- **MQTT:** lightweight publish/subscribe messaging is suitable for sending state snapshots to a dashboard or monitoring service.

## Engineering limitations and improvements
1. Digital IR modules are not equivalent to automotive-grade presence sensors.
2. A single instantaneous sample may flicker; add a stability window and hysteresis.
3. Sensor disconnection should be distinguished from a vacant bay in a production system.
4. MQTT reconnect logic, TLS and secure credential storage require further hardening.
5. The current firmware has a fixed four-slot layout and does not provide remote control or access authorization.

## References
- Espressif Systems, ESP8266 Arduino Core documentation: https://arduino-esp8266.readthedocs.io/
- PlatformIO, ESP8266 platform documentation: https://docs.platformio.org/en/latest/platforms/espressif8266.html
- Adafruit SSD1306 library: https://github.com/adafruit/Adafruit_SSD1306
- Adafruit GFX library: https://github.com/adafruit/Adafruit-GFX-Library
- NXP, PCF8574 remote 8-bit I/O expander datasheet: https://www.nxp.com/docs/en/data-sheet/PCF8574_PCF8574A.pdf
- OASIS, MQTT Version 3.1.1 specification: https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html
- Eclipse Paho / PubSubClient ecosystem: https://github.com/knolleary/pubsubclient

References are provided for technical background; no claim is made that every cited component has been bench-tested in this project.
