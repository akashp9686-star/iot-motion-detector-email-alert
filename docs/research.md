# Technical Research — PIR Motion Detection and IFTTT Alerts

## PIR sensing
The HC-SR501 is a passive infrared motion sensor module. It detects changes in infrared energy across its sensing zones and provides a digital output. Detection depends on module adjustment, warm-up time, field of view, target movement, temperature and placement. It is not a camera or identity-recognition device.

## ESP8266 role
The ESP8266 NodeMCU reads the PIR digital output and controls a low-voltage indicator LED. Its integrated Wi-Fi provides connectivity to the IFTTT Webhooks service. GPIO pins use 3.3V logic and are not 5V tolerant; verify the PIR output voltage for the exact board revision.

## Webhook notification flow
When the PIR input transitions from LOW to HIGH, firmware sends an HTTPS request to the IFTTT Webhooks event endpoint. The configured IFTTT Applet then performs an email action. The firmware applies a 60-second cooldown after an HTTP 200 response. An HTTP success response indicates webhook acceptance, not proof that an email reached the recipient's inbox.

## Security and reliability considerations
- Treat the webhook key as a password; never commit it or expose it in screenshots.
- Demo firmware uses permissive TLS certificate handling; production deployments must validate the server certificate.
- Wi-Fi outages, service outages, email filtering, sensor placement and false detections can interrupt alerts.
- This educational prototype is not a certified security alarm or life-safety device.

## References
- Glowlogics IoT Projects Handbook, Project 04.
- Espressif ESP8266 Arduino Core: https://arduino-esp8266.readthedocs.io/
- IFTTT Webhooks documentation: https://ifttt.com/maker_webhooks
- HC-SR501 module documentation: verify the datasheet for the exact purchased module revision.

References provide implementation background; no physical sensor or notification test is claimed by this document.
