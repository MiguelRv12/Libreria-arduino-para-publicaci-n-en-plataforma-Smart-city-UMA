/*

  Fiware.cpp 
  Miguel Rodriguez
*/

#include "Fiware.h"
#include "Arduino.h"

HTTPClient http;

Fiware::Fiware(){
}
void Fiware::SetUl2Server(String URL,String port,String Token,String ID){
	_URL = URL;
	_port = port;
	_Token = Token;
	_ID = ID;
}
void Fiware::ultralightSend(String body){
  _httpCode = 0;
  
  Serial.println("\nSENDING DATA TO IoTAgent - Ultralight");
  Serial.println("   http://" + _URL + ":" + _port + "/iot/d?k=" + _Token + "&i=" + _ID + "&getCmd=1");
  
  // Configure URL and headers
  http.begin("http://" + _URL + ":" + _port + "/iot/d?k=" + _Token + "&i=" + _ID + "&getCmd=1");
  http.addHeader("Content-Type", "text/plain");

  // Execute request and get response payload 
  _httpCode = http.POST(body);
  String payload = http.getString();

  //Print HTTP response
  Serial.print("   Request executed.Return code: ");
  Serial.print(_httpCode);
  Serial.print(". Response payload: ");
  Serial.println(payload);

  //Close connection
  http.end();  
  if (_httpCode ==200){
       Serial.println("Data sent successfully to FIWARE\n\n");
    }
    else{
      Serial.println("Failure sending data to FIWARE\n\n");
    }
}

UL2Payload::UL2Payload(){
	
}
void UL2Payload::add(String field, String value){
	if ( _UL2message == ""){
		_UL2message = field +"|"+ value ;
	}
	else{
		_UL2message =  _UL2message + "|"+field +"|"+ value;
	}
}
void UL2Payload::add(String field, int value){
	if ( _UL2message == ""){
		_UL2message = field +"|"+ value ;
	}
	else{
		_UL2message =  _UL2message + "|"+field +"|"+ value;
	}
}
void UL2Payload::add(String field, double value){
	if ( _UL2message == ""){
		_UL2message = field +"|"+ value ;
	}
	else{
		_UL2message =  _UL2message + "|"+field +"|"+ value;
	}
}
void UL2Payload::add(String field, boolean value){
	if ( _UL2message == ""){
		_UL2message = field +"|"+ value;
	}
	else{
		_UL2message =  _UL2message +"|"+ field +"|"+ value;
	}
}
void UL2Payload::add(String field, char value){
	if ( _UL2message == ""){
		_UL2message = field +"|"+ value ;
	}
	else{
		_UL2message =  _UL2message + "|"+field +"|"+ value;
	}
}
String UL2Payload::GetString(){
	Serial.println(_UL2message);
	return _UL2message;
}
