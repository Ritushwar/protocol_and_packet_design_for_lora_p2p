#include <Arduino.h>
#include "serial_io.h"
#include "lora_packet.h"
#include "protocol_state.h"
#include "crc.h"

uint8_t u_id_s = 0x01;
uint8_t n_id_s = 0x01;
uint8_t u_id_r = 0x00;
uint8_t n_id_r = 0x00;

static uint16_t my_crc_polynomial = 0xA001;

static uint8_t my_aes_key[16] = {
    '1','2','3','4','5','6','7','8',
    '9','0','a','b','c','d','e','f'
};

void setup(){
    serialIO_init(9600);

    set_my_add(u_id_s, n_id_s);
    set_r_add(u_id_r, n_id_r);
    Serial.println("Type something to send and Enter:");

    setup_lora_communication();
    set_polynomial(my_crc_polynomial);
}

void loop(){
    // function to handle input from serial monitor
    serial_update();

    // function to handle packet coming from lora
    lora_update();

    // function to handle operate and fsm transition
    fsm_update();
}