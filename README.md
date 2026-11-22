# Project 04 — IoT Motion Detector with Email Alert
**Glowlogics IoT Projects Handbook | MEDIUM | ESP8266 NodeMCU + HC-SR501 PIR + IFTTT Webhooks**

An ESP8266 reads an HC-SR501 PIR sensor. When motion is detected, the firmware turns on a local LED and sends an IFTTT Webhooks event configured to send an email (or another supported notification). A cooldown limits repeated alerts.

## Handbook component checklist
- ESP8266 NodeMCU ×1
- HC-SR501 PIR sensor ×1
- LED + 220Ω resistor ×1
- Jumper wires ×5
- Breadboard ×1

## Exact handbook pin mapping
| Component | NodeMCU connection |
|---|---|
| PIR VCC | VIN / 5V (confirm module supply rating) |
| PIR GND | GND |
| PIR OUT | D2 / GPIO4 |
| LED anode through 220Ω | D1 / GPIO5 |
| LED cathode | GND |

ESP8266 GPIO is 3.3V logic and is not 5V tolerant. Confirm PIR OUT high voltage from the exact module revision; use appropriate level conversion if required.

## IFTTT setup
1. Sign in at https://ifttt.com.
2. Create an Applet: If This = Webhooks, receive a web request with event name `motion_detected`.
3. Then That = Gmail / Email, send an alert email.
4. Open Webhooks documentation and copy the private key.
5. Configure `WIFI_SSID`, `WIFI_PASSWORD`, and `IFTTT_WEBHOOK_KEY` in private build settings.
6. Keep the event name identical and never publish the key.

## Firmware behavior
- PIR input D2; LED output D1.
- Webhook triggered on a LOW-to-HIGH motion edge.
- 60-second cooldown after successful HTTP 200 response.
- Serial Monitor: 115200 baud.
- PlatformIO target: `env:nodemcuv2`.

## Build
```bash
pio run -e nodemcuv2
pio run -e nodemcuv2 -t upload
pio device monitor -b 115200
```

## Verification record
| Check | Status |
|---|---|
| Firmware compilation | Check latest GitHub Actions run |
| Physical PIR motion detection | Not performed / no evidence supplied |
| LED response | Not performed / no evidence supplied |
| Wi-Fi association | Not performed / no evidence supplied |
| IFTTT webhook and email receipt | Not performed / no evidence supplied |
| Cooldown behavior | Not performed / no evidence supplied |

Do not report any physical or service test as passed until actually performed and recorded. A green CI build is not hardware validation.

## Safety and limitations
Educational prototype only; not a certified alarm or life-safety device. PIR may miss or falsely detect motion. Keep the circuit low voltage and dry. The demo firmware uses permissive TLS certificate handling for ease of setup; production deployments must validate the server certificate and protect the webhook key.

## References
- Glowlogics IoT Projects Handbook, Project 04.
- ESP8266 Arduino Core: https://arduino-esp8266.readthedocs.io/
- IFTTT Webhooks: https://ifttt.com/maker_webhooks
