#ifndef LORA_PACKET_H
#define LORA_PACKET_H

#include <Arduino.h>
#include <string>
#include <stdint.h>
// #define PKT_TYPE    0
// #define FLAGS       1
// #define NODE_ID_S   2
// #define USER_ID_S   3
// #define NODE_ID_R   4
// #define USER_ID_R   5
// #define MSG_ID      6
// #define PAY_LEN     7
// #define CRC_MSB     8
// #define CRC_LSB     9

// today change
// set external variable
// payload size suitable for AES

// packets types
extern const uint8_t PKT_RTS;
extern const uint8_t PKT_CTS;
extern const uint8_t PKT_DATA;
extern const uint8_t PKT_ACK;
extern const uint8_t PKT_HEADER;
extern const uint8_t PKT_RETRY;
extern const uint8_t PKT_ERROR;


// flags
extern const uint8_t FLAG_RTS;
extern const uint8_t FLAG_CTS;
extern const uint8_t FLAG_SENT;
extern const uint8_t FLAG_DEL;
extern const uint8_t FLAG_ERROR;
extern const uint8_t FLAG_DATA;
extern const uint8_t FLAG_ACK;


struct __attribute__((packed)) lora_packet_struct{
    uint8_t PKT_TYPE;
    uint8_t FLAGS;
    uint8_t USER_ID_S;
    uint8_t NODE_ID_S;
    uint8_t USER_ID_R;
    uint8_t NODE_ID_R;
    uint8_t MSG_ID;
    uint8_t PAY_LEN;
    uint8_t PAYLOAD[63];    // 63 bytes
    uint8_t CRC_UB;         // crc upper byte
    uint8_t CRC_LB;         // crc lower byte
};

lora_packet_struct get_rts(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
lora_packet_struct get_cts(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
lora_packet_struct get_data_pkt(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t *, size_t, uint16_t);
lora_packet_struct get_ack(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
lora_packet_struct get_retry(uint8_t, uint8_t, uint8_t, uint8_t,uint8_t);
#endif