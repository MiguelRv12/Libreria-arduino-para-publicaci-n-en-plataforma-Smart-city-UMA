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


#define get_command std::function<void(String)> callback


class fiwareULClient{
	private:
	int _httpCode;
	int _state;
	int _polltime;
	int _port;
	String _URL;
	String _Token;
	String _ID;
	String _payload;
	String _command;
	unsigned long _now;
	boolean _publishPoll;
	get_command;
	public:
		fiwareULClient ();
		void setServer(String URL,int port,String Token,String ID);
		int publish(String body);
		void setCallback(get_command);
		void setPoolInterval(int polltime);
		void setPoolOnPublish(boolean publishPoll);
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
