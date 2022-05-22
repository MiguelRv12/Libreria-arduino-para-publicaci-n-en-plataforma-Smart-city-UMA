/*
  Fiware.h 
  Miguel Rodriguez
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


class Fiware {
	private:
	int _httpCode;
	String _URL;
	String _port;
	String _Token;
	String _ID;
	public:
		Fiware();
		void SetUl2Server(String URL,String port,String Token,String ID);
		void ultralightSend(String body);
		
};
class UL2Payload {
	private:
	String _UL2message;
	public:
		UL2Payload();
		void add(String field, String value);
		void add(String field, int value);
		void add(String field, double value);
		void add(String field, boolean value);
		void add(String field, char value);
		String GetString();
		
};
