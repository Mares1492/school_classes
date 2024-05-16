/**
   BasicHTTPSClient.ino

    Created on: 20.08.2018

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
// Fingerprint for demo URL, expires on June 2, 2021, needs to be updated well before this date
//36 AB B5 84 1E F1 AA C2 8E 4B 50 24 B2 A3 70 55 FB 96 F2 43
//0x36, 0xAB, 0xB5, 0x84, 0x1E, 0xF1, 0xAA, 0xC2, 0x8E, 0x4B, 0x50, 0x24, 0xB2, 0xA3, 0x70, 0x55, 0xFB, 0x96, 0xF2, 0x43
//const uint8_t fingerprint[20] = {0x36, 0xAB, 0xB5, 0x6b, 0xec, 0x90, 0x22, 0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3};
//0x04, 0xDF, 0x17, 0x1B, 0xDE, 0x0C, 0xC6, 0x4C, 0xB9, 0x76, 0xB6, 0x80,  0x78, 0x2A, 0x32, 0xBD, 0x85, 0x39, 0xF1, 0x26
//const uint8_t fingerprint[20] = {0x36, 0xAB, 0xB5, 0x84, 0x1E, 0xF1, 0xAA, 0xC2, 0x8E, 0x4B, 0x50, 0x24, 0xB2, 0xA3, 0x70, 0x55, 0xFB, 0x96, 0xF2, 0x43};
//5A 48 5B 27 A7 FB 0B D6 63 83 8E 8E 80 DB 29 B7 2C 72 A8 8E
const uint8_t fingerprint[20] = {0x09 ,0x1E ,0x68 ,0x9F ,0xBD ,0x40 ,0x4B ,0x47 ,0x8D ,0xAC ,0xBE ,0xFE ,0xEF ,0x35 ,0xD6 ,0x52 ,0xC1 ,0xA0 ,0xEC ,0x9F};

ESP8266WiFiMulti WiFiMulti;

unsigned long previousMillis = 0;     
const long interval = 1000; 
int yesButtonPin = D1;
int noButtonPin = D2;
bool isButtonPressed = false;
void setup() {

  Serial.begin(115200);
  pinMode(yesButtonPin, INPUT);
  pinMode(noButtonPin, INPUT);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("TLU", "");
}

void loop() {
  int nr = analogRead(A0);
  
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    // client->setInsecure();

    HTTPClient https;
    unsigned long currentMillis = millis();
    //Interaval web call
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      String response = "";
      if(digitalRead(yesButtonPin)){
        if(!isButtonPressed){
          response = "true";
          isButtonPressed = true;
        }
      }
      else if(digitalRead(noButtonPin)){
        if(!isButtonPressed){
          response = "false";
          isButtonPressed = true;
        }
      }
      else if(!digitalRead(yesButtonPin) && !digitalRead(noButtonPin)){
        isButtonPressed = false;
      }
      if(response == ""){
        return;
      }
      String path = "https://script.google.com/macros/s/AKfycbyc4gn94hqyvQ5oft8UbOlwkoZjuo8Obsv54N9eUtFy40Cw70E5_3Qxre3VXxfedmr8/exec?player2=";
      Serial.print("[HTTPS] begin...\n");
      //if (https.begin(*client, "https://docs.google.com/spreadsheets/d/1i8IXemCzEZvEQXV_ZrzpHzpdE0_ZR91-PPsu4JZuDFQ/export?format=csv")) {  // HTTPS
      if (https.begin(*client, path+response)) {  // HTTPS
      //Kirjutage lehele ja / ei, tuli vastavalt p�leb v�i mitte
      //Looge kaks tulukest, kummalegi oma lahter. 

        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

          // file found at server
        // if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        // }
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }

        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
    }
  }
  
}