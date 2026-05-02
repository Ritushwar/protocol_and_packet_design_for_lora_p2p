#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include "mbedtls/aes.h"
#include <Arduino.h>
#include <stdint.h>
#include <string>

void set_aes_key(uint8_t[16]);    // 16 bytes of key
void encrypt_msg(std::string&);
void decrypt_msg(std::string&);

#endif