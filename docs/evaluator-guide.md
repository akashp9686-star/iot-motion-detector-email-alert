# Evaluator Guide — Glowlogics Project 04

## Project
IoT Motion Detector with Email Alert — ESP8266 NodeMCU, HC-SR501 PIR, LED indicator and IFTTT Webhooks email action.

## Review path
1. Project overview and verification boundary: `README.md`.
2. Firmware: `src/main.cpp`.
3. Build target: `platformio.ini`.
4. Architecture and wiring: `docs/architecture.md`, `docs/wiring.md`.
5. IFTTT event configuration: `README.md`.
6. Research, tests and review checklist: `docs/research.md`, `docs/testing.md`, `docs/review-checklist.md`.

## Reproducible software check
Install PlatformIO and run `pio run -e nodemcuv2`. Configure Wi-Fi and the IFTTT Webhooks key privately before attempting a live notification test.

## Verification boundary
CI compilation does not verify PIR sensing, LED operation, Wi-Fi association, webhook delivery or receipt of email. These tests remain pending until performed and evidenced. The repository is an educational source-code submission, not a certified alarm.