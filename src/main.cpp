#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "config.h"
#ifndef WIFI_SSID
#define WIFI_SSID "YOUR_WIFI_NAME"
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#endif
#ifndef IFTTT_WEBHOOK_KEY
#define IFTTT_WEBHOOK_KEY "YOUR_IFTTT_WEBHOOK_KEY"
#endif
#ifndef IFTTT_EVENT_NAME
#define IFTTT_EVENT_NAME "motion_detected"
#endif
// Glowlogics Project 04. PIR OUT -> D2/GPIO4; LED + 220 ohm -> D1/GPIO5.
// Ensure PIR OUT is 3.3V-compatible; ESP8266 GPIO is not 5V tolerant.
static const uint8_t PIR_PIN=D2, LED_PIN=D1;
static const unsigned long COOLDOWN_MS=60000UL, WIFI_TIMEOUT_MS=20000UL;
static const char HOST[]="maker.ifttt.com";
unsigned long lastAlert=0; bool sentBefore=false, previousMotion=false;
bool connectWifi(){
  if(WiFi.status()==WL_CONNECTED) return true;
  WiFi.mode(WIFI_STA); WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  unsigned long start=millis();
  while(WiFi.status()!=WL_CONNECTED && millis()-start<WIFI_TIMEOUT_MS){ delay(250); yield(); }
  return WiFi.status()==WL_CONNECTED;
}
bool sendWebhook(){
  if(String(IFTTT_WEBHOOK_KEY)=="YOUR_IFTTT_WEBHOOK_KEY"){ Serial.println(F("Set private IFTTT webhook key.")); return false; }
  WiFiClientSecure client; client.setInsecure(); // Demo only; validate TLS certificate in production.
  client.setTimeout(8000);
  if(!client.connect(HOST,443)){ Serial.println(F("IFTTT HTTPS connection failed")); return false; }
  String path=String(F("/trigger/"))+IFTTT_EVENT_NAME+F("/with/key/")+IFTTT_WEBHOOK_KEY;
  client.print(String(F("GET "))+path+F(" HTTP/1.1\r\nHost: ")+HOST+F("\r\nConnection: close\r\n\r\n"));
  unsigned long start=millis();
  while(!client.available() && client.connected() && millis()-start<8000){ delay(50); yield(); }
  String status=client.readStringUntil('\n'); Serial.print(F("IFTTT response: ")); Serial.println(status);
  bool ok=status.indexOf("200")>=0; client.stop(); return ok;
}
void setup(){
  Serial.begin(115200); pinMode(PIR_PIN,INPUT); pinMode(LED_PIN,OUTPUT); digitalWrite(LED_PIN,LOW);
  Serial.println(F("Glowlogics Project 04 - PIR Motion Detector")); Serial.println(F("Allow HC-SR501 to stabilize."));
  connectWifi();
}
void loop(){
  bool motion=digitalRead(PIR_PIN)==HIGH; digitalWrite(LED_PIN,motion?HIGH:LOW);
  if(motion && !previousMotion){
    Serial.println(F("Motion detected."));
    if(!sentBefore || millis()-lastAlert>=COOLDOWN_MS){
      if(connectWifi() && sendWebhook()){ lastAlert=millis(); sentBefore=true; Serial.println(F("Webhook accepted; verify email action.")); }
    } else Serial.println(F("Alert suppressed by cooldown."));
  }
  previousMotion=motion; delay(100);
}