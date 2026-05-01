#include <Arduino.h>
#include "serial_io.h"
#include "lora_packet.h"
#include "text_protocol.h"
#include "setup_lora.h"
uint8_t u_id_s = 0x00;
uint8_t n_id_s = 0x00;
uint8_t u_id_r = 0x01;
uint8_t n_id_r = 0x01;
void setup(){
    serialIO_init(9600);

    set_my_add(u_id_s, n_id_s);
    set_r_add(u_id_r, n_id_r);
    Serial.println("Type something to send and Enter:");

    setup_lora_communication();
}

void loop(){
    if(serialIO_available()){
        std:: string msg = serialIO_read();

        int msg_len = msg.length();
        serialIO_print("Received text: " + msg);
        Serial.println("Msg length: " + String(msg_len));
        perform_handshake();
        Serial.println("Initial handshake done:");
    }
    // if lora packet is received
    if(receivedFlag){
        Serial.println("LoRa packet is detected");
        handle_packet();
    }
}