#ifndef CRC_H
#define CRC_H
#include <Arduino.h>
#include <stdint.h>

void set_polynomial(uint16_t);
uint16_t calc_crc_bytes(uint8_t *, size_t );
#endif
