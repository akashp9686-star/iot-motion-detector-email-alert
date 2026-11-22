# Submission Review Checklist

## Repository completeness
- [x] Public GitHub repository created
- [x] Project overview and objectives documented
- [x] Firmware source included
- [x] PlatformIO configuration included
- [x] Hardware inventory and pin map documented
- [x] Architecture and data flow documented
- [x] Wiring and electrical safety notes included
- [x] MQTT topic and payload documented
- [x] Research references included
- [x] Synthetic sample dataset and Python tests included
- [x] GitHub Actions workflow included
- [ ] Latest hosted CI run reviewed and passing
- [ ] Physical prototype assembled and tested (not claimed)
- [ ] Physical test evidence and photographs added (not supplied)

## Important scope statement
The project is prepared as a repository-based engineering submission. Software builds and synthetic-data checks are not substitutes for physical hardware validation. Confirm with the evaluator that repository-based evaluation is accepted before representing this work as a completed physical prototype.

## Reviewer notes
- Sensor output polarity must be checked against the exact IR module used.
- I2C addresses must be confirmed on the actual OLED and PCF8574 boards.
- ESP8266 inputs and I2C lines must remain within 3.3 V logic limits.
- LED driver current limits and PCF8574 module wiring must be checked before powering.
- MQTT integration needs a live broker test before it can be called verified.
