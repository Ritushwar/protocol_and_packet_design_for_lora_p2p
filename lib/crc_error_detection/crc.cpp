#include "crc.h"

uint16_t crc_polynomial;

void set_polynomial(uint16_t my_poly){
    crc_polynomial = my_poly;
}

uint16_t calc_crc_bytes(uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF;   // initial value

    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];  // XOR with current byte

        for (int j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;  // polynomial
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}