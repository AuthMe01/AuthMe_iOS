#pragma once

#define AES256_GCM_KEY_SIZE    32
#define AES256_GCM_IV_SIZE     12
#define AES256_GCM_TAG_SIZE    16

namespace AuthMe
{

int gcm_encrypt(const unsigned char *plaintext, int plaintext_len,
                const unsigned char *aad, int aad_len,
                const unsigned char *key,
                const unsigned char *iv, int iv_len,
                unsigned char *ciphertext,
                unsigned char *tag);

int gcm_decrypt(const unsigned char *ciphertext, int ciphertext_len,
                const unsigned char *aad, int aad_len,
                const unsigned char *tag,
                const unsigned char *key,
                const unsigned char *iv, int iv_len,
                unsigned char *plaintext);
}