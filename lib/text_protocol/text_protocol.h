#ifndef TEXT_PROTOCOL_H
#define TEXT_PROTOCO_H

#include <stdint.h>
// #include "lora_packet.h"
// #include "setup_lora.h"

extern uint8_t my_user_id;
extern uint8_t my_node_id;

extern uint8_t user_id_r;
extern uint8_t node_id_r;


void set_my_add(uint8_t, uint8_t);
void set_r_add(uint8_t, uint8_t);
void send_message();
void develop_msg_packet(const std::string&);
void perform_handshake();
void handle_packet();
void perform_two_way_handshake();
void respone_rts();
#endif