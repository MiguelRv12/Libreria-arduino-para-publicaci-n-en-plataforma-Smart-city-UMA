/*

  Fiware.cpp 
  Miguel Rodriguez Valencia

*/

#include "Fiware.h"
#include "Arduino.h"

HTTPClient http;

fiwareULClient::fiwareULClient(){		
	_state = FW_NO_SETUP; // FW server not initially configured
	_polltime = 50;
	_publishPoll = false;
}
void fiwareULClient::setServer(String URL,int port,String Token,String ID){
	_URL = URL;
	_port = port;
	_Token = Token;
	_ID = ID;
	_state = FW_PUBLISH_OK; //Fw server configured
	if ( DEBUG_MSG == 1){
		Serial.println("Fiware server initialized");
	}
}
int fiwareULClient::publish(String body){
  _httpCode = -1;
  int code;
  if(_state == -1){ //We don't do anything if FW serves has not been configured
  	Serial.println("Error:No FW server initialized");
	code = -1;
  }
  else{	
  	Serial.println("\nSENDING DATA TO IoTAgent - Ultralight");
  	Serial.println("   http://" + _URL + ":" + _port + "/iot/d?k=" + _Token + "&i=" + _ID + "&getCmd=1");
  
  	// Configure URL and headers
  	http.begin("http://" + _URL + ":" + _port + "/iot/d?k=" + _Token + "&i=" + _ID + "&getCmd=1");
  	http.addHeader("Content-Type", "text/plain");

  	// Execute request and get response payload 
  	_httpCode = http.POST(body);
  	_payload = http.getString();

 	//Print HTTP response
  	Serial.print("   Request executed.Return code: ");
  	Serial.print(_httpCode);
  	Serial.print(". Response payload: ");
  	Serial.println(_payload);

  	//Close connection
  	http.end();  
 	 if (_httpCode ==200){
      	 	Serial.println("Data sent successfully to FIWARE\n\n");
		code = 0;
  	 }
   	 else{
     	 	Serial.println("Failure sending data to FIWARE\n\n");
		code = _httpCode;
		if ( DEBUG_MSG == 1){
			Serial.println("Http error "+_httpCode);
		}
   	 }
	if (_publishPoll == true){
		http.begin("http://" + _URL + ":" + _port + "/iot/d?k=" + _Token + "&i=" + _ID + "&getCmd=1");
  			http.addHeader("Content-Type", "text/plain");

  			// Execute request and get response payload 
  			_httpCode = http.GET();
  			_payload = http.getString();

 			//Print HTTP response
  			Serial.print("   Request executed.Return code: ");
  			Serial.print(_httpCode);
  			Serial.print(". Response payload: ");
  			Serial.println(_payload);
		
  			//Close connection
  			http.end(); 
			if (_httpCode ==200){
      	 			StringTokenizer payload(_payload,String("#"));
  				do
				{
    					_command=payload.nextToken(); // Return a command
					if ( DEBUG_MSG == 1){
						Serial.println("Checking " + _command);
					}
					callback(_command); // we send the command to the callback
					http.begin("http://" + _URL + ":" + _port + "/iot/d?k=" + _Token + "&i=" + _ID + _command + "|OK");
					http.end();
				} while (payload.hasNext() == true);
  	 		}
   	 		else{
     	 			Serial.println("Failure to receive data from FIWARE\n\n");
				if ( DEBUG_MSG == 1){
					Serial.println("Http error "+_httpCode);
				}
   			 }	
	}
	return code;
  }
}
void fiwareULClient::setCallback(get_command){
	while(_publishPoll = false){	// Check if we should constantly check for a command
		if ( DEBUG_MSG == 1){
			Serial.println("Checking input commands each"+ _polltime );
		}
		unsigned long last_msg=0;
		_now=millis();
		if(_now - last_msg >=_polltime){ // Check how often we should check for a command
			if ( DEBUG_MSG == 1){
				Serial.println("Checking input commands now");
			}
			last_msg = _now;
 			// Configure URL and headers
  			http.begin("http://" + _URL + ":" + _port + "/iot/d?k=" + _Token + "&i=" + _ID + "&getCmd=1");
  			http.addHeader("Content-Type", "text/plain");

  			// Execute request and get response payload 
  			_httpCode = http.GET();
  			_payload = http.getString();

 			//Print HTTP response
  			//Serial.print("   Request executed.Return code: ");
  			//Serial.print(_httpCode);
  			//Serial.print(". Response payload: ");
  			//Serial.println(_payload);
		
  			//Close connection
  			http.end(); 
			if (_httpCode ==200){
      	 			StringTokenizer payload(_payload,String("#"));
  				do
				{
    					_command=payload.nextToken(); // Return a command
					if ( DEBUG_MSG == 1){
						Serial.println("Checking " + _command);
					}
					callback(_command); // we send the command to the callback
					http.begin("http://" + _URL + ":" + _port + "/iot/d?k=" + _Token + "&i=" + _ID + _command + "|OK");
					http.end();
				} while (payload.hasNext() == true);
  	 		}
   	 		else{
     	 			Serial.println("Failure to receive data from FIWARE\n\n");
				if ( DEBUG_MSG == 1){
					Serial.println("Http error "+_httpCode);
				}
   			 }
  			
			
		}
  	}
 
}
void fiwareULClient::setPoolInterval(int polltime){
	if (polltime < 50){
		_polltime = 50;
	}
	else{
		_polltime = polltime;
	}
		if ( DEBUG_MSG == 1){
			Serial.println("PollTime set up to " + _polltime);
		}
}
void fiwareULClient::setPoolOnPublish(boolean publishPoll){
	_publishPoll = publishPoll;
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
void UL2Payload::add(String field,const char* value){
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
void UL2Payload::cleanPayload(){
	_UL2message = "";
}
