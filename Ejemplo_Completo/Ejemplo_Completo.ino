#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHTesp.h";
#include "Fiware.h"
#include <StringTokenizer.h>

//HTTPClient http;                        //Declare object of class HTTPClient
DHTesp dht;

// Update these with values suitable for your network.
const char* ssid = "Miguelwifi";
const char* password = "puessipuessi";
const char* FIWARE_apikey = "xraet1pdnumsjohoa0ybu5uoc";
const char* FIWARE_server = "150.214.58.178";
int FIWARE_port= 7896;
const char* FIWARE_device_ID= "D_HC_prueba";

// cadenas para topics e ID
char ID_PLACA[16];

// GPIOs
int LED1 = 2;  
int LED2 = 16; 
int httpCode;
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
void callback(String command) {
    if ( command == "Led"){
        digitalWrite(LED2, LOW); 
        delay(100);
        digitalWrite(LED2, HIGH);  
    }
}
//-----------------------------------------------------
//     SETUP
//-----------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Empieza setup...");
  
  dht.setup(5, DHTesp::DHT11);
  pinMode(LED1, OUTPUT);    // inicializa GPIO como salida
  pinMode(LED2, OUTPUT);    
  digitalWrite(LED1, HIGH); // apaga el led
  digitalWrite(LED2, HIGH); 
  // crea topics usando id de la placa
  sprintf(ID_PLACA, "ESP_%d", ESP.getChipId());
  conecta_wifi();
  Serial.printf("Identificador placa: %s\n", ID_PLACA );
  Serial.printf("Termina setup en %lu ms\n\n",millis());
  fiware.setServer(FIWARE_server,FIWARE_port,FIWARE_apikey,FIWARE_device_ID);
  fiware.setPoolOnPublish(false);
  fiware.setPoolInterval(100000);
  fiware.setCallback(callback);
}

//-----------------------------------------------------
#define TAMANHO_MENSAJE 128
unsigned long ultimo_mensaje=0;
//-----------------------------------------------------
//     LOOP
//-----------------------------------------------------
void loop() {
  unsigned long ahora = millis();
  if (ahora - ultimo_mensaje >= 1000) {
        digitalWrite(LED2, LOW); 
        delay(100);
        digitalWrite(LED2, HIGH);  
    ultimo_mensaje = ahora;
    Payload.add("T",dht.getTemperature());
    Payload.add("H",dht.getHumidity());
    UL2 = Payload.GetString();
    httpCode=fiware.publish(UL2);
    if (httpCode==0){
      Payload.cleanPayload();
    }
  }
}
