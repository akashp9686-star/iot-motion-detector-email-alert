# Testing and Verification Record

## Evidence policy
A successful CI run proves only the software checks actually executed by that workflow. It does not prove physical sensor operation, OLED display behavior, LED wiring, Wi-Fi association, or delivery to a live MQTT broker.

## Automated checks
GitHub Actions is configured to:
1. Validate the sample CSV using Python unit tests.
2. Build the ESP8266 firmware with MQTT disabled.
3. Build the ESP8266 firmware with MQTT enabled using a temporary CI-only placeholder secrets header.

The Actions tab is the authoritative record of the latest workflow result.

## Test matrix

| Test | Method | Current status |
|---|---|---|
| Sample data schema and slot counts | Python unit tests | Automated in CI |
| Default firmware compile | PlatformIO | Automated in CI |
| MQTT firmware compile | PlatformIO | Automated in CI |
| Four physical IR sensors | Hardware test | Not performed / evidence pending |
| OLED I2C display | Hardware test | Not performed / evidence pending |
| PCF8574 and eight LEDs | Hardware test | Not performed / evidence pending |
| Wi-Fi connection | Hardware/network test | Not performed / evidence pending |
| Live MQTT broker publish/subscribe | Integration test | Not performed / evidence pending |
| Long-duration reliability | Field test | Not performed / evidence pending |

## Physical test procedure (when hardware is available)
1. Inspect power rails, common ground, I2C pull-up voltage and GPIO voltage compatibility before powering.
2. Run an I2C scanner and record OLED and expander addresses.
3. Test each IR sensor individually and record raw logic level for empty and occupied conditions.
4. Confirm each bay updates the OLED and its corresponding red/green indicators.
5. Test Wi-Fi and MQTT using a private test broker; save a sanitized subscriber log without credentials.
6. Test false triggers under different lighting, sensor alignment and repeated vehicle approach/removal.
7. Record board, sensor module, firmware commit, date, observations and photographs.

No physical test is marked as passed in this repository without evidence.
