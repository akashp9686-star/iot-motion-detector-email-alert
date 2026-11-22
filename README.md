# Project 04 — IoT Motion Detector with Email Alert
**Glowlogics IoT Projects Handbook | MEDIUM | ESP8266 NodeMCU + HC-SR501 PIR + IFTTT Webhooks**

An ESP8266 reads an HC-SR501 PIR sensor. When motion is detected, firmware turns on a local LED and sends an IFTTT Webhooks event configured to send an email. A 60-second cooldown limits repeated alerts.

## Handbook component checklist
- ESP8266 NodeMCU ×1
- HC-SR501 PIR sensor ×1
- LED + 220Ω resistor ×1
- Jumper wires ×5
- Breadboard ×1

## Pin mapping
| Component | NodeMCU |
|---|---|
| PIR VCC | VIN / 5V (verify module rating) |
| PIR GND | GND |
| PIR OUT | D2 / GPIO4 |
| LED anode through 220Ω | D1 / GPIO5 |
| LED cathode | GND |

ESP8266 GPIO is 3.3V logic and is not 5V tolerant. Confirm PIR OUT voltage for the exact module; level-shift if needed.

## IFTTT setup
1. Create an IFTTT Applet: If This = Webhooks, receive a web request event named `motion_detected`.
2. Then That = Gmail / Email, send an alert email.
3. Copy the Webhooks key privately.
4. Copy `include/config.example.h` to `include/config.h` and set Wi-Fi SSID, password and IFTTT key. Keep the file untracked.
5. Keep event name identical to the Applet. Never publish the webhook key.

## Build
```bash
pio run -e nodemcuv2
pio run -e nodemcuv2 -t upload
pio device monitor -b 115200
```

## Firmware behavior
PIR input D2; LED output D1. A LOW-to-HIGH motion edge triggers an HTTPS Webhook request. Cooldown is 60 seconds after an HTTP 200 response. An HTTP 200 confirms the webhook endpoint response, not guaranteed email inbox delivery.

## Verification
| Check | Status |
|---|---|
| Hosted firmware compilation | See latest GitHub Actions result |
| PIR detection / LED | Not physically tested |
| Wi-Fi / IFTTT / email receipt | Not tested |
| Cooldown behavior | Not physically tested |

Do not mark physical or cloud tests passed until actually performed and evidenced.

## Safety and limitations
Educational notification prototype only; not a certified alarm or life-safety device. PIR may miss or falsely detect motion. Keep the circuit low voltage and dry. Demo firmware uses permissive TLS certificate handling; production deployments must validate the server certificate and protect the webhook key.

## References
- Glowlogics IoT Projects Handbook, Project 04.
- ESP8266 Arduino Core: https://arduino-esp8266.readthedocs.io/
- IFTTT Webhooks: https://ifttt.com/maker_webhooks
