#include "serial_io.h"

static std::string ipBuffer = "";
static bool messageReady = false;

void serialIO_init(unsigned long baudRate){
    Serial.begin(baudRate);
    ipBuffer.clear();
    messageReady = false;
}

bool serialIO_available(){
    while (Serial.available())
    {
        char c = Serial.read();

        if(c =='\n'){
            messageReady = true;
            return true;
        }

        else if (c != '\r')
        {
            ipBuffer += c;
        }
        
    }
    return messageReady;
}

std::string serialIO_read(){
    messageReady = false;
    std::string temp = ipBuffer;
    ipBuffer.clear();
    return temp;
}

void serialIO_print(const std::string& msg){
    Serial.println(msg.c_str());
}

