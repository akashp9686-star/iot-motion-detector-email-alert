# MQTT Interface

## Build selection
- `nodemcuv2`: MQTT disabled; no credentials required.
- `nodemcuv2-mqtt`: MQTT enabled; requires a local `include/secrets.h`.

Copy `include/secrets.example.h` to `include/secrets.h` and set:
- `WIFI_SSID`
- `WIFI_PASSWORD`
- `MQTT_HOST`
- `MQTT_PORT` (optional; defaults to 1883)
- `MQTT_USER` and `MQTT_PASSWORD` (optional)

The local secrets file is ignored by Git. Never paste real credentials into issues, commits, screenshots or public logs.

## Topic
Default topic: `parking/site-a/status`

## Example JSON
```json
{
  "device": "smart-parking-01",
  "slots": [
    {"slot": 1, "occupied": false},
    {"slot": 2, "occupied": true},
    {"slot": 3, "occupied": false},
    {"slot": 4, "occupied": true}
  ],
  "available": 2,
  "occupied": 2
}
```

The firmware publishes a retained state snapshot after a detected change and periodically. Broker availability, firewall rules, authentication and TLS are deployment-specific. The sample configuration uses plain MQTT and should only be used on a trusted test network. For internet-facing deployments, use TLS-capable transport, broker authentication, unique credentials and topic access controls.
