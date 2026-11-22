# Evaluator Guide — Project 04

## Project
IoT Smart Parking Management System — ESP8266, four digital IR sensors, SSD1306 OLED, PCF8574 LED expander and optional MQTT.

## What to review
- Firmware: `src/main.cpp`
- Build configuration: `platformio.ini`
- Pin and device settings: `include/project_config.h`
- Safe MQTT configuration template: `include/secrets.example.h`
- Architecture and wiring: `docs/architecture.md`, `docs/wiring.md`
- MQTT interface: `docs/mqtt.md`
- Research, tests and review checklist: `docs/research.md`, `docs/testing.md`, `docs/review-checklist.md`

## Reproducible software checks
1. Install PlatformIO.
2. Run `pio run -e nodemcuv2` for the standard build.
3. Copy `include/secrets.example.h` to `include/secrets.h` and configure private values before attempting a local MQTT build.
4. Run `pio run -e nodemcuv2-mqtt`.
5. Run `python -m unittest discover -s tests -v`.

GitHub Actions run #3 completed successfully for both firmware environments and the sample-data test job: https://github.com/akashp9686-star/iot-smart-parking-management-system/actions/runs/45000896452

## Scope and evidence
The sample CSV is synthetic. The successful CI workflow verifies compilation and sample-data checks only. Four physical IR sensors, OLED, PCF8574 indicators, Wi-Fi and a live MQTT broker have not been physically verified. The proposed wiring and sensor active-level setting must be checked against the exact hardware modules before powering the circuit.

## Evaluator request
Please assess the source code, architecture, wiring and safety documentation, MQTT design, research references, sample-data tests and hosted CI results. Please advise whether repository-based evaluation is accepted and whether a physical demonstration or further evidence is mandatory.
