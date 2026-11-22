# System Architecture

## Functional blocks
1. Four digital IR modules provide one occupancy input per parking bay.
2. ESP8266 samples each input and normalizes its active logic level using `SENSOR_ACTIVE_LEVEL`.
3. The controller computes occupied and available totals.
4. An SSD1306 I2C OLED presents the four bay states and summary.
5. A PCF8574 I2C expander controls eight indicator outputs: one green and one red LED per bay.
6. Optional MQTT publishes a retained JSON snapshot over Wi-Fi.

## State model
Each slot has a binary state:
- `occupied = false`: bay is treated as vacant; green indicator on.
- `occupied = true`: bay is treated as occupied; red indicator on.

The firmware currently uses direct digital readings without temporal filtering. A production design should add debounce / stability filtering and a sensor-fault state to avoid flicker or false occupancy.

## Communication
I2C connects the OLED and PCF8574 on the same SDA/SCL pair. MQTT is optional at compile time. The default build does not need Wi-Fi credentials. The MQTT build requires a local, ignored `include/secrets.h`.

## Design boundaries
The current design is a four-slot educational prototype. It does not include cloud account management, mobile app authentication, vehicle identification, payment, barrier control, or safety-rated detection.
