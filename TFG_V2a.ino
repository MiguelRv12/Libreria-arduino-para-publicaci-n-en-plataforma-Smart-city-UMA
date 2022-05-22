#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Fiware.h"

//HTTPClient http;                        //Declare object of class HTTPClient

// Update these with values suitable for your network.
const char* ssid = "Miguelwifi";
const char* password = "puessipuessi";
const char* FIWARE_apikey = "xraet1pdnumsjohoa0ybu5uoc";
const char* FIWARE_server = "150.214.58.178";
const char* FIWARE_port= "7896";
const char* FIWARE_device_ID= "D_HC_prueba";

// cadenas para topics e ID
char ID_PLACA[16];

// GPIOs
int LED1 = 2;  
int LED2 = 16; 

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
Fiware fiware;
UL2Payload Payload;
//-----------------------------------------------------
//     SETUP
//-----------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Empieza setup...");
  pinMode(LED1, OUTPUT);    // inicializa GPIO como salida
  pinMode(LED2, OUTPUT);    
  digitalWrite(LED1, HIGH); // apaga el led
  digitalWrite(LED2, HIGH); 
  // crea topics usando id de la placa
  sprintf(ID_PLACA, "ESP_%d", ESP.getChipId());
  conecta_wifi();
  Serial.printf("Identificador placa: %s\n", ID_PLACA );
  Serial.printf("Termina setup en %lu ms\n\n",millis());
  Payload.add("T",25.5);
  Payload.add("H",45);
  Payload.add("m","28");
  Payload.add("b",true);
  Payload.add("c",'a');
  
  UL2 = Payload.GetString();
}

//-----------------------------------------------------
#define TAMANHO_MENSAJE 128
unsigned long ultimo_mensaje=0;
//-----------------------------------------------------
//     LOOP
//-----------------------------------------------------
void loop() {
  unsigned long ahora = millis();
  if (ahora - ultimo_mensaje >= 30000) {
    ultimo_mensaje = ahora;
    fiware.SetUl2Server(FIWARE_server,FIWARE_port,FIWARE_apikey,FIWARE_device_ID);
    fiware.ultralightSend(UL2);
    digitalWrite(LED2, LOW); // enciende el led al enviar mensaje
  }
  if (digitalRead(LED2)==LOW && ahora-ultimo_mensaje>=100) {
    digitalWrite(LED2, HIGH); 
  }
}
