#include <Arduino.h>
#include "serial_io.h"

void setup(){
    serialIO_init(9600);
    Serial.println("Type something to send and Enter:");
}

void loop(){
    if(serialIO_available()){
        std:: string msg = serialIO_read();

        int msg_len = msg.length();
        serialIO_print("Received text: " + msg);
        Serial.println("Msg length: " + String(msg_len));
    }
}