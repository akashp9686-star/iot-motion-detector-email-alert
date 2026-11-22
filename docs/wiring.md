# Wiring and Electrical Notes

## ESP8266 connections

| Signal | NodeMCU | GPIO |
|---|---|---:|
| I2C SCL | D1 | GPIO5 |
| I2C SDA | D2 | GPIO4 |
| IR sensor 1 digital output | D5 | GPIO14 |
| IR sensor 2 digital output | D6 | GPIO12 |
| IR sensor 3 digital output | D7 | GPIO13 |
| IR sensor 4 digital output | D0 | GPIO16 |

## Shared I2C bus
- OLED SDA/SCL to NodeMCU D2/D1.
- PCF8574 SDA/SCL to the same D2/D1 lines.
- Confirm actual I2C addresses using an I2C scanner before operation. Typical addresses are OLED 0x3C and PCF8574 0x20, but modules vary.
- Connect grounds together.

## LED expander mapping
- P0–P3: green LEDs for bays 1–4.
- P4–P7: red LEDs for bays 1–4.
- The firmware assumes HIGH means LED ON. Some modules or transistor boards invert this logic; adapt the output map after checking the circuit.
- Use a separate current-limiting resistor for each LED. Check PCF8574 per-pin and total-current limits; use transistor drivers if needed.

## Electrical safety
- ESP8266 GPIO is 3.3 V logic and is not 5 V tolerant.
- Never connect a 5 V sensor output directly to an ESP8266 pin. Use a level shifter or a verified 3.3 V-compatible output.
- Ensure I2C pull-ups are to 3.3 V, not 5 V.
- Use a regulated supply with adequate current capacity and common ground.
- Disconnect power before changing wiring.
- Do not connect mains voltage to this prototype.

**Important:** This is a proposed pin map and wiring plan, not evidence that a physical circuit has been assembled or tested.
