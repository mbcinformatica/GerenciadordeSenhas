#include <Arduino.h>
#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#include <IRremote.hpp>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <Wire.h> 
#include <FS.h>


#define mtIDENTIFICAR 0
#define mtGET 1
#define mtPOST 2
#define mtOUTRO 3

void configModeCallback();
void configModeCallback(WiFiManager *myWiFiManager);


unsigned long delayClose;
WiFiServer server(81);
WiFiClient client;
String header;

void setup() {

  Serial.begin(115200);
  IrSender.begin();
  IrSender.enableIROut(38);
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.autoConnect("ESP_AP", "123456789");
  if (!MDNS.begin("paineldesenhas")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) { delay(100); }
  }
  Serial.println("mDNS responder started");
  server.begin();
  Serial.println("TCP server started");
  MDNS.addService("http", "tcp", 81);
  delay(100);
}

void loop() {
  
}


void saveConfigCallback() {

  Serial.println("Configuração Salva");
  Serial.println(WiFi.softAPIP());
}

void configModeCallback(WiFiManager *myWiFiManager) {

  Serial.println("Entrou no Modo de Configuração!!!");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}
