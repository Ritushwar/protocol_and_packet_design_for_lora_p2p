// This is to design the correct header format for two way reliable communication using lora

/*  
  Byte 0: Packet Type      (1B)
  Byte 1: Flag / Status    (1B)
  Byte 2  : Node ID (Sender)   (1B)
  Byte 3  : User ID (Sender)   (1B)
  Byte 4  : Node ID (Receiver) (1B)
  Byte 5  : User ID (Receiver) (1B)
  Byte 6  : Message ID         (1B)
  Byte 7  : Payload Length     (1B)
  Byte 8  : CRC (MSB)          (1B)
  Byte 9  : CRC (LSB)          (1B)
--------------------------------
  Byte 10+: Payload (N bytes)
*/

// let's define constraints

#include "lora_packet.h"

const uint8_t PKT_RTS    = 0x01;
const uint8_t PKT_CTS    = 0x02;
const uint8_t PKT_DATA   = 0x03;
const uint8_t PKT_ACK    = 0x04;
const uint8_t PKT_HEADER = 0x05;

const uint8_t FLAG_RTS   = 0x01;
const uint8_t FLAG_CTS   = 0x02;
const uint8_t FLAG_SENT  = 0x04;
const uint8_t FLAG_DEL   = 0x08;
const uint8_t FLAG_ERROR = 0x10;
const uint8_t FLAG_RETRY = 0x20;
const uint8_t FLAG_DATA  = 0x40;
const uint8_t FLAG_ACK   = 0x80;

struct lora_packet{
    uint8_t PKT_TYPE;
    uint8_t FLAGS;
    uint8_t USER_ID_S;
    uint8_t NODE_ID_S;
    uint8_t USER_ID_R;
    uint8_t NODE_ID_R;
    uint8_t MSG_ID;
    uint8_t PAY_LEN;
    uint8_t PAYLOAD[56];
};

// it will return RTS packet
lora_packet_struct get_rts(uint8_t user_id_s , uint8_t node_id_s, uint8_t user_id_r, uint8_t node_id_r, uint8_t msg_id){
    lora_packet_struct my_pkt = {0};
    my_pkt.PKT_TYPE = PKT_RTS;
    my_pkt.FLAGS = FLAG_RTS;
    my_pkt.USER_ID_S = user_id_s;
    my_pkt.NODE_ID_S = node_id_s;
    my_pkt.USER_ID_R = user_id_r;
    my_pkt.NODE_ID_R = node_id_r;
    my_pkt.MSG_ID = msg_id;
    my_pkt.PAY_LEN = 0x00;
    return my_pkt;
}

// it will return CTS packet
lora_packet_struct get_cts(uint8_t user_id_s, uint8_t node_id_s, uint8_t user_id_r, uint8_t node_id_r, uint8_t msg_id){
  lora_packet_struct my_pkt = {0};
  my_pkt.PKT_TYPE = PKT_CTS;
  my_pkt.FLAGS = FLAG_CTS;
  my_pkt.USER_ID_S = user_id_s;
  my_pkt.NODE_ID_S = node_id_s;
  my_pkt.USER_ID_R = user_id_r;
  my_pkt.NODE_ID_R = node_id_r;
  my_pkt.MSG_ID = msg_id;
  my_pkt.PAY_LEN = 0x00;
  return my_pkt;
}

// it will return cts packet
lora_packet_struct get_data_pkt(uint8_t user_id_s, uint8_t node_id_s, uint8_t user_id_r, uint8_t node_id_r, uint8_t msg_id, const std::string msg){
  lora_packet_struct my_pkt = {0};
  my_pkt.PKT_TYPE = PKT_DATA;
  my_pkt.FLAGS = FLAG_DATA;
  my_pkt.USER_ID_S = user_id_s;
  my_pkt.NODE_ID_S = node_id_s;
  my_pkt.USER_ID_R = user_id_r;
  my_pkt.NODE_ID_R = node_id_r;
  my_pkt.MSG_ID = msg_id;
  my_pkt.PAY_LEN = msg.length();

  if(my_pkt.PAY_LEN > sizeof(my_pkt.PAYLOAD)){
    my_pkt.PAY_LEN = sizeof(my_pkt.PAYLOAD);  // trucate the packet
  }
  memcpy(my_pkt.PAYLOAD, msg.c_str(), my_pkt.PAY_LEN);
  return my_pkt;
}

// it will return ack packet
lora_packet_struct get_ack(uint8_t user_id_s, uint8_t node_id_s, uint8_t user_id_r, uint8_t node_id_r, uint8_t msg_id){
  lora_packet_struct my_pkt = {0};
  my_pkt.PKT_TYPE = PKT_ACK;
  my_pkt.FLAGS = FLAG_ACK;
  my_pkt.USER_ID_S = user_id_s;
  my_pkt.NODE_ID_S = node_id_s;
  my_pkt.USER_ID_R = user_id_r;
  my_pkt.NODE_ID_R = node_id_r;
  my_pkt.MSG_ID = msg_id;
  my_pkt.PAY_LEN = 0x00;
  return my_pkt;
}



