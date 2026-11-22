# Project 04 — IoT Motion Detector with Email Alert
**Glowlogics IoT Projects Handbook | MEDIUM | ESP8266 + HC-SR501 PIR + IFTTT Webhook**

This repository follows handbook Project 04. An ESP8266 reads an HC-SR501 PIR sensor. On motion, it lights a local LED and triggers an IFTTT Webhooks event configured to send an email (or another supported notification). A cooldown prevents repeated alerts.

**Verification status:** Firmware and setup instructions are provided. Physical PIR detection, Wi-Fi connection, IFTTT webhook delivery and email receipt have not been claimed as tested.

## Components (handbook)
ESP8266 NodeMCU (1); PIR sensor HC-SR501 (1); LED + 220 ohm resistor (1); jumper wires (5); breadboard (1).

## Wiring
- PIR VCC -> ESP8266 VIN / 5V (verify module supply specification).
- PIR GND -> ESP8266 GND.
- PIR OUT -> ESP8266 D2 / GPIO4.
- LED anode through 220 ohm -> ESP8266 D1 / GPIO5.
- LED cathode -> GND.
ESP8266 GPIO is 3.3V only and is not 5V tolerant. Verify PIR OUT logic level; level-shift if needed.

## IFTTT setup
1. Sign in at https://ifttt.com.
2. Create an Applet: If This = Webhooks, receive a web request; event name motion_detected.
3. Then That = Gmail / Email, send an alert email.
4. Open Webhooks documentation and copy the private key.
5. Configure WIFI_SSID, WIFI_PASSWORD and IFTTT_WEBHOOK_KEY privately. Keep the event name identical to the Applet.
6. Never publish the webhook key.

## Firmware behavior
Reads PIR digital output; LED follows motion; sends webhook on a LOW-to-HIGH motion edge; applies a 60-second cooldown after successful HTTP 200 response. Serial Monitor baud: 115200. Firmware source: src/main.cpp. PlatformIO target: env:nodemcuv2.

## Testing checklist
- [ ] Confirm PIR supply and output voltage from exact module datasheet.
- [ ] Confirm serial motion detection and LED indication.
- [ ] Confirm Wi-Fi connection.
- [ ] Trigger IFTTT event and verify actual email receipt.
- [ ] Verify cooldown and record date, board revision and observations.
These tests remain pending until actually performed.

## Safety and limitations
Educational prototype only, not a certified alarm or life-safety device. PIR sensors may miss or falsely detect motion due to placement, temperature, sunlight, pets and settings. Do not rely on it for security-critical monitoring. Keep wiring low voltage and dry. Demo firmware uses permissive TLS certificate handling; production use must validate the server certificate and protect the webhook key.

## References
- Glowlogics IoT Projects Handbook, Project 04.
- ESP8266 Arduino Core: https://arduino-esp8266.readthedocs.io/
- IFTTT Webhooks: https://ifttt.com/maker_webhooks
- HC-SR501 exact module datasheet (verify supplier revision).