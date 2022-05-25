/*
  Fiware.h 
  Miguel Rodriguez
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266HTTPClient.h>
#include <StringTokenizer.h>


#define FW_PUBLISH_OK  0
#define FW_NO_SETUP  -1

class fiwareULClient{
	private:
	int _httpCode;
	String _URL;
	int _port;
	String _Token;
	String _ID;
	int _state;
	int _polltime;
	String _payload;
	boolean _publishPoll;
	String _command;
	unsigned long _now;
	public:
		fiwareULClient ();
		void setServer(String URL,int port,String Token,String ID);
		int publish(String body);
		setCallback(get_command);
		setPoolInterval(int polltime);
		setPoolOnPublish(boolean publishPoll);
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
		void add(String field, const char* value);
		String GetString();
		
};
