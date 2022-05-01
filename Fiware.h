/*
  Fiware.h 
  Miguel Rodriguez
*/
#include “Arduino.h”





class Fiware : public Print {

private:

const char* apikey;
const char* server;
const char* port;
const char* device_ID;
const char* Body;
public:

boolean	ultralightSend(const char* apikey,const char* server,const char* port,const char* device_ID,const char* body);




};
class UL2 : public Print {

private:

public:

const char* Temp;
const char* Hum;
};
/*
objeto_FW mifiware(server, port, device, key);
miobjeto
miobjeto.add
mifiware.send
*/