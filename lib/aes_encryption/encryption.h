#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include "mbedtls/aes.h"
#include <Arduino.h>
#include <stdint.h>
#include <string>

void set_aes_key(uint8_t[16]);    // 16 bytes of key
size_t encrypt_msg(uint8_t[64], size_t, uint8_t[64]);
void decrypt_msg(uint8_t[64], size_t, uint8_t[64]);
#endif