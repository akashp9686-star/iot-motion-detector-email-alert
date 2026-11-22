# Project 04 — Wiring
| Component | NodeMCU |
|---|---|
| HC-SR501 VCC | VIN / 5V (confirm sensor board supply rating) |
| HC-SR501 GND | GND |
| HC-SR501 OUT | D2 / GPIO4 |
| LED anode through 220 ohm resistor | D1 / GPIO5 |
| LED cathode | GND |

ESP8266 GPIO is 3.3V logic and is not 5V tolerant. Verify the PIR module's OUT high voltage; level-shift if it can exceed 3.3V. Confirm the module's pin labels and supply range before connection. Allow the PIR module to stabilize after power-up.

All connections shown are low-voltage prototype wiring. Disconnect power before changing connections.
