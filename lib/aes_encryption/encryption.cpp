#include "encryption.h"


static uint8_t kw[16];

// set the encryption key
void set_aes_key(uint8_t key[16]) {
    memcpy(kw, key, 16);
}

// PKCS7 pad + AES-CBC encrypt → result replaces msg content (raw bytes as string)
size_t encrypt_msg(uint8_t *input, size_t len, uint8_t *output) {
    
    // PKCS7 padding
    size_t padded_len = ((len / 16) + 1) * 16;
    uint8_t pad_byte = padded_len - len;

    uint8_t plain[padded_len];
    memcpy(plain, input, len);
    memset(plain + len, pad_byte, pad_byte);

    uint8_t iv[16] = {0};
    mbedtls_aes_context ctx;

    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_enc(&ctx, kw, 128);

    mbedtls_aes_crypt_cbc(&ctx, MBEDTLS_AES_ENCRYPT,
                          padded_len, iv, plain, output);

    mbedtls_aes_free(&ctx);

    return padded_len;  // return new length
}

// AES-CBC decrypt + remove PKCS7 padding → result replaces msg content
void decrypt_msg(uint8_t cipher[64], size_t cipher_len, uint8_t plain_out[64]) {

    if (cipher_len == 0 || cipher_len % 16 != 0) {
        Serial.println("[AES] decrypt error: invalid length");
        return;
    }

    uint8_t iv[16] = {0};
    uint8_t temp_plain[64] = {0};

    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_dec(&ctx, kw, 128);

    mbedtls_aes_crypt_cbc(
        &ctx,
        MBEDTLS_AES_DECRYPT,
        cipher_len,
        iv,
        cipher,
        temp_plain
    );
    mbedtls_aes_free(&ctx);

    // PKCS7 validation
    uint8_t pad_byte = temp_plain[cipher_len - 1];
    size_t actual_len = cipher_len;

    if (pad_byte > 0 && pad_byte <= 16) {
        bool valid = true;
        for (size_t i = cipher_len - pad_byte; i < cipher_len; i++) {
            if (temp_plain[i] != pad_byte) {
                valid = false;
                break;
            }
        }
        if (valid) {
            actual_len = cipher_len - pad_byte;
        } else {
            Serial.println("[AES] invalid PKCS7 padding");
            return;
        }
    }

    // Safe copy + null terminate
    memcpy(plain_out, temp_plain, actual_len);
    if (actual_len < 64) {
        plain_out[actual_len] = '\0';
    }
}