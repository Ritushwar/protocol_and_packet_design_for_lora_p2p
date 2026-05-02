#include "encryption.h"


static uint8_t kw[16];

// set the encryption key
void set_aes_key(uint8_t key[16]) {
    memcpy(kw, key, 16);
}

// PKCS7 pad + AES-CBC encrypt → result replaces msg content (raw bytes as string)
void encrypt_msg(std::string &msg) {
    // 1. PKCS7 padding
    size_t orig_len   = msg.length();
    size_t padded_len = ((orig_len / 16) + 1) * 16;   // always add at least 1 pad byte
    uint8_t pad_byte  = (uint8_t)(padded_len - orig_len);

    uint8_t plain[padded_len];
    memcpy(plain, msg.c_str(), orig_len);
    memset(plain + orig_len, pad_byte, padded_len - orig_len);

    // 2. Fixed IV (all zeros — swap for random IV in production)
    uint8_t iv[16] = {0};

    // 3. Encrypt
    uint8_t cipher[padded_len];
    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_enc(&ctx, kw, 128);
    mbedtls_aes_crypt_cbc(&ctx, MBEDTLS_AES_ENCRYPT, padded_len, iv, plain, cipher);
    mbedtls_aes_free(&ctx);

    // 4. Write raw cipher bytes back into msg
    msg.assign((char*)cipher, padded_len);
}

// AES-CBC decrypt + remove PKCS7 padding → result replaces msg content
void decrypt_msg(std::string &msg) {
    size_t cipher_len = msg.length();

    // Must be a multiple of 16
    if (cipher_len == 0 || cipher_len % 16 != 0) {
        Serial.println("[AES] decrypt error: invalid length");
        return;
    }

    uint8_t iv[16]  = {0};
    uint8_t plain[cipher_len];

    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_dec(&ctx, kw, 128);
    mbedtls_aes_crypt_cbc(&ctx, MBEDTLS_AES_DECRYPT, cipher_len, iv,
                          (uint8_t*)msg.data(), plain);
    mbedtls_aes_free(&ctx);

    // Remove PKCS7 padding
    uint8_t pad_byte = plain[cipher_len - 1];
    size_t  actual_len = (pad_byte > 0 && pad_byte <= 16)
                         ? cipher_len - pad_byte
                         : cipher_len;

    msg.assign((char*)plain, actual_len);
}