#pragma once
#include <vector>
#include <string>

#define AES256_GCM_KEY_SIZE    32
#define AES256_GCM_IV_SIZE     12
#define AES256_GCM_TAG_SIZE    16

namespace AuthMe
{
bool JwtRs256TokenVerify(const std::string rsa_pub_key, const std::string token);

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

bool X509CertVerify(const char* cert_pem, const char* root_pem);

std::vector<unsigned char> SHA256Hash(const void* data, unsigned int data_len);

std::vector<unsigned char> RSASign_sha256(const unsigned char* data, unsigned int data_len, const char* rsa_key);

bool RSAVerify_sha256(const unsigned char* data,
                      unsigned int data_len,
                      const unsigned char* sig,
                      unsigned int sig_len,
                      const char* x509_crt);

std::vector<unsigned char> RSAEncrypt(const std::string& rsaPublicKey, const unsigned char *plaintext, int plaintextLen);

std::vector<unsigned char> RSADecrypt(const std::string& rsaPrivateKey, const unsigned char *cipher, int cipherLen);

void RandomByes(unsigned char* buffer, int size);

int GetRSAPrivateKeySize(const std::string& rsaPrivateKey);

}
