/*

  Fiware.cpp 
  Miguel Rodriguez
*/

#include "Fiware.h"
#include "Arduino.h"


boolean	ultralightSend(const char* apikey,const char* server,const char* port,const char* device_ID,const char* body){
  int httpCode = 0;
  
  Serial.println("\nSENDING DATA TO IoTAgent - Ultralight");
  Serial.println("   http://" + URL + ":" + port + "/iot/d?k=" + Token + "&i=" + ID + "&getCmd=1");
  
  // Configure URL and headers
  http.begin("http://" + URL + ":" + port + "/iot/d?k=" + Token + "&i=" + ID + "&getCmd=1");
  http.addHeader("Content-Type", "text/plain");

  // Execute request and get response payload 
  httpCode = http.POST(Body);
  String payload = http.getString();

  //Print HTTP response
  Serial.print("   Request executed.Return code: ");
  Serial.print(httpCode);
  Serial.print(". Response payload: ");
  Serial.println(payload);

  //Close connection
  http.end();  
  if (httpCode ==200){
       Serial.println("Data sent successfully to FIWARE\n\n");
    }
    else{
      Serial.println("Failure sending data to FIWARE\n\n");
    }
}