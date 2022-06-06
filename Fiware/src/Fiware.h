/*

  Fiware.h 
  Miguel Rodriguez Valencia

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <StringTokenizer.h> //Librarie used while gettind differents commands


#define FW_PUBLISH_OK  0 //State if FW server has been set up
#define FW_NO_SETUP  -1  //State if FW server has not been set up
#define DEBUG_MSG 0	// 1 if you want to see dbug msgs, 0 if not.


#define get_command std::function<void(String)> callback	//Callback function definition


class fiwareULClient{	//class related to sending and receiving messages
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
		void setServer(String URL,int port,String Token,String ID); //Configure Fiware server initially
		int publish(String body); //Publish a message in the server that has been set-up
		void setCallback(get_command);// sets how and where callback will work
		void setPoolInterval(int polltime);// set each how many time callback will check messages
		void setPoolOnPublish(boolean publishPoll); // set if callback will check each polltime or just when a message is sent.
};
class UL2Payload { //This class declares the message that is going to be send to by FIware
	private:
	String _UL2message;
	public:
		UL2Payload();
		// adds the specific type of value to the payload of the message
		void add(String field, String value);
		void add(String field, int value);
		void add(String field, double value);
		void add(String field, boolean value);
		void add(String field, char value);
		void add(String field, const char* value);

		void cleanPayload(); // Restores Payload String
		String GetString();  // Returns Actual Payload
		
};
