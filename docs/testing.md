# Project 04 — Testing and Verification
## Software verification
GitHub Actions compiles the ESP8266 NodeMCU PlatformIO target. Check the Actions tab for the latest result. A successful compile does not prove physical sensing or notification delivery.

## Test matrix
| Test | Status |
|---|---|
| PIR detects motion at D2 | Not performed |
| LED follows PIR output | Not performed |
| Wi-Fi association | Not performed |
| IFTTT Webhooks HTTP response | Not performed |
| Actual email received | Not performed |
| 60-second cooldown behavior | Not performed |

## Physical/service test procedure
1. Verify PIR supply and output voltage from the exact module datasheet.
2. Observe serial output while moving through the sensor's field of view.
3. Confirm LED behavior.
4. Configure the IFTTT Webhooks event and email action.
5. Confirm Wi-Fi connection, trigger the event and verify the email arrives.
6. Repeat motion within and after the cooldown; record actual behavior.

Record the board revision, sensor revision, firmware commit, date and evidence. Do not mark tests passed until performed.
