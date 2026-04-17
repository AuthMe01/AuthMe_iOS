//#pragma once
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#include "engine_service_type.h"
//
//void AuthMe_ReleaseImage(AuthMeImage* pImage);
//
////long AuthMe_CreateModel(const char* modelName, const char* modelPath);
//
////long AuthMe_CreateModel_Stream(const char* modelName, const void* buffer, int size);
//
//int AuthMe_GetModelInfo(long model, const char* modelName, const int jsonStringMaxLenght, char* const jsonString);
//
//int AuthMe_ReleaseModel(long model, const char* modelName);
//
//// usage:
//// long model = AuthMe_CreateModel(modelName, modelPath);
//// char* version = AuthMe_GetModelVersion(modelName, model);
//// need to free() the return value
//char* AuthMe_GetModelVersion(const char* modelName, long model);
//
///*
//public key format
//-----BEGIN PUBLIC KEY-----
//...
//-----END PUBLIC KEY-----
//
//need to free() the return value
//*/
//char* AuthMe_EncryptString(const char* plaintext, const char* publicKey);
//
///* private key format
//-----BEGIN RSA PRIVATE KEY-----
//...
//-----END RSA PRIVATE KEY-----
//
//need to free() the return value
//*/
//char* AuthMe_DecryptString(const char* cipherBase64, const char* privateKey);
//
////need to free() the return value
//char* AuthMe_EncryptWithRSAPrivateKey( const char* plaintext );
//
////need to free() the return value
//char* AuthMe_DecryptWithRSAPublicKey( const char* encryptedText, const char* publickey );
//
//#ifdef __cplusplus
//}
//#endif