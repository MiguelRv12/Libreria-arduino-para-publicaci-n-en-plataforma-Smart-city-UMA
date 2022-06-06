#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Fiware.h"


// Update these with values suitable for your network.
const char* ssid = "Wifiname";
const char* password = "WifiPassword";
const char* FIWARE_apikey = "apikey";
const char* FIWARE_server = "xxx.xxx.xx.xxx";
int FIWARE_port= yyyy;
const char* FIWARE_device_ID= "ID";

// Chains for topics and ID
char Board_ID[16]; 

String UL2;
//-----------------------------------------------------
void conecta_wifi() {
  Serial.printf("\nConnecting to %s:\n", ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.printf("\nWiFi connected, IP address: %s\n", WiFi.localIP().toString().c_str());
}
fiwareULClient  fiware;
UL2Payload Payload;
//-----------------------------------------------------
//     SETUP
//-----------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting setup...");
  
  // Create topics using board ID
  sprintf(Board_ID, "ESP_%d", ESP.getChipId());
  conecta_wifi();
  Serial.printf("Board Identificator: %s\n", Board_ID );
  Serial.printf("Set-up ends in %lu ms\n\n",millis());
  Payload.add("T",25.5);
  Payload.add("H",45);
  Payload.add("m","28");
  Payload.add("b",true);
  Payload.add("c",'a');
  
  UL2 = Payload.GetString();
}

//-----------------------------------------------------
#define Message_size 128
unsigned long Last_message=0;
//-----------------------------------------------------
//     LOOP
//-----------------------------------------------------
void loop() {
  unsigned long now = millis();
  if (now - Last_message >= 30000) {
    Last_message = now;
    fiware.setServer(FIWARE_server,FIWARE_port,FIWARE_apikey,FIWARE_device_ID);
    fiware.publish(UL2);
  }
  
}
