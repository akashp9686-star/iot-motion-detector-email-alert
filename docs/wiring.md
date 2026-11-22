# Project 04 — Handbook Wiring
| Component | NodeMCU |
|---|---|
| HC-SR501 VCC | VIN / 5V (verify module supply rating) |
| HC-SR501 GND | GND |
| HC-SR501 OUT | D2 / GPIO4 |
| LED anode through 220Ω resistor | D1 / GPIO5 |
| LED cathode | GND |

ESP8266 GPIO is 3.3V logic and is not 5V tolerant. Confirm PIR OUT voltage using the exact sensor-board revision; level-shift if the output can exceed 3.3V. Confirm module pin labels and supply range before powering. Allow the HC-SR501 to stabilize after power-up.

All listed connections are low-voltage prototype wiring. Disconnect power before changing connections.
