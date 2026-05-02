#ifndef SETUP_LORA_H
#define SETUP_LORA_H

#include <Arduino.h>
#include <SPI.h>
#include "lora_packet.h"

// LoRa Frequency
const long frequency = 433E6;
extern volatile bool receivedFlag;
// extern static int _last_pkt_size;
// ESP32 ↔ LoRa pin mapping
const int cs    = 5;   // NSS
const int reset = 2;   // RESET
const int dio0  = 22;   // DIO0 (RX interrupt)

const int led_when_receive = 26;  // Blinks on packet receive
const int led_on_t_mode    = 25;  // ON = transmitting mode

void setup_lora_communication();
void setMode(int);
void send_msg(std::string&);
std::string get_msg();
void send_packet(const lora_packet_struct&);
int get_packet_size();
lora_packet_struct get_packet(int);
bool is_packet_available();
#endif