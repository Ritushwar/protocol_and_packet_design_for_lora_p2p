#include <Arduino.h>
#include "serial_io.h"
#include "setup_lora.h"

void setup(){
    serialIO_init(9600);
    Serial.println("Type something to send and Enter:");
    setup_lora_communication();
}

void loop(){
    if(serialIO_available()){
        std:: string msg = serialIO_read();

        int msg_len = msg.length();
        serialIO_print("Received text: " + msg);
        Serial.println("Msg length: " + String(msg_len));

        // send message through lora
        send_msg(msg);

    }

    if(receivedFlag){
        std::string my_msg;
        my_msg = get_msg();
        serialIO_print("Received text: " + my_msg); 
    }
}