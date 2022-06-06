Fiware
======
An Arduino for sending and reciving messages from the plataform Smart city from telefonica
Uploaded in https://github.com/MiguelRv12/Libreria-arduino-para-publicaci-n-en-plataforma-Smart-city-UMA
Original Written by Miguel Rodriguez <Miguel.Rodriguez.valencia@gmail.com>

This library intention is to make much easier the connection throught fiware of arduino ESP8266 and Smar city from Telefonica.

In this library we can see Two classes, the first one is used for sending and reciving Data and all the aux functions we need,
the second one is for setting up the message for the data. This classes are:

fiwareULClient
UL2Payload



The function for each class are:
fiwareULClient
	setServer (set up fiware server)
	publish	(Publish message in the fiware server)
	setCallback (Set the function for the call back and send the commands there)
	setPoolInterval	(Set how often do we check for commands in the call back
	setPoolOnPublish (Set if we check callback eachPoolInterval or when we publish)
UL2Payload
	add (add data in Fiware format)
		Type of data:
		String
		int
		Double
		Boolean
		Char
		Const Char*
	cleanPayload (Resets Payload)
	GetString ( Return Payload as a String)






