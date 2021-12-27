#ifndef _IOS_CHTSE_H
#define _IOS_CHTSE_H
 
#define IOS_CHTSE_VERSION                          0x01000000UL
 
#include <time.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
    /** @brief Initialize PKCS#11 cryptoki library
      * Initialize PKCS#11 cryptoki library, allocate resources
      * @param filepath  [in] PKCS#11 cryptoki library file path
      * @param initArgs  [in] reserved, set to NULL
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long Initialize(const char* filepath, void* initArgs);
 
    /** @brief Finalize PKCS#11 cryptoki library, release resources
      * generate Finalize PKCS#11 cryptoki library, release resources
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long Finalize(void);
 
    /** @brief Get the ID of all slots
      * Get the ID of all slots
      * @param slotIDs  [out] array of slot ID
      * @param slotIDLen  [in, out] length of slotIDs
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long GetSlotIDs(unsigned long* slotIDs, unsigned long* slotIDLen);
 
    /** @brief Get the description of slot
      * Get the description of slot
      * @param slotID  [in] ID of slot
      * @param slotDesc  [out] description of slot
      * @param slotDescLen  [in, out] length of slotDesc
      * @return result
      * @retval 0 success
      * @retval 0x3 CKR_SLOT_ID_INVALID
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long GetSlotDesc(unsigned long slotID, unsigned char* slotDesc, unsigned long* slotDescLen);
 
    /** @brief check token present
      * Check if the token exists
      * @param slotID  [in] ID of slot
      * @param present  [out] 1 for exist, 0 for not exist
      * @return result
      * @retval 0 success
      * @retval 0x3 CKR_SLOT_ID_INVALID
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long IsTokenPresent(unsigned long slotID, int* present);
 
    /** @brief Get the serial number of token
      * Get the serial number of token
      * @param slotID  [in] ID of slot
      * @param tokenSerialNumber  [out] serial number of token
      * @param tokenSerialNumberLen  [in, out] length of tokenSerialNumber
      * @return result
      * @retval 0 success
      * @retval 0x3 CKR_SLOT_ID_INVALID
      * @retval 0x32 CKR_DEVICE_REMOVED
      * @retval 0xE0 CKR_TOKEN_NOT_PRESENT
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long GetTokenSerialNumber(unsigned long slotID, unsigned char* tokenSerialNumber, unsigned long* tokenSerialNumberLen);
 
    /** @brief Open session
      * Open a session
      * @param slotID  [in] ID of slot
      * @param flag  [in] read only: 4, read/write: 6
      * @param session  [out] session id
      * @return result
      * @retval 0 success
      * @retval 0x3 CKR_SLOT_ID_INVALID
      * @retval 0x32 CKR_DEVICE_REMOVED
      * @retval 0xE0 CKR_TOKEN_NOT_PRESENT
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long OpenSession(unsigned long slotID, unsigned long flag, unsigned long* session);
 
    /** @brief Close session
      * Close a session
      * @param session  [in] session ID
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long CloseSession(unsigned long session);
 
    /** @brief Login
      * Login
      * @param session  [in] session id
      * @param pin  [in] pin code of token
      * @param pinLen  [in] length of pin
      * @param type  [in] USER=1, SO=0
      * @return result
      * @retval 0 success
      * @retval 0xA0 CKR_PIN_INCORRECT
      * @retval 0xA2 CKR_PIN_LEN_RANGE
      * @retval 0xA4 CKR_PIN_LOCKED
      * @retval 0x32 CKR_DEVICE_REMOVED
      * @retval 0xE0 CKR_TOKEN_NOT_PRESENT
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long Login(unsigned long session, unsigned char* pin, unsigned long pinLen, unsigned long type);
 
    /** @brief Logout
      * Logout
      * @param session  [in] session id
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long Logout(unsigned long session);
 
    /** @brief Get number of keys
      * Get number of keys
      * @param session [in] session id
      * @param keyNum [out] number of keys
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long GetKeyNum(unsigned long session, unsigned long* keyNum);
 
    /** @brief Get key ID
      * Get key ID
      * @param session [in] session id
      * @param keyIndex  [in] index of key
      * @param id [out] ID of the key
      * @param idLen [in, out] length of id
      * @return result
      * @retval 0 success
      * @retval 0x10000007 ARGUMENTS_BAD
      * @retval 0x10000150 BUFFER_TOO_SMALL
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long GetKeyID(unsigned long session, unsigned long keyIndex, unsigned char* id, unsigned long* idLen);
 
    /** @brief Get key handle by ID
      * Get key handle by ID
      * @param session [in] session id
      * @param id [in] ID of the key
      * @param idLen [in] length of id
      * @param type [in] PRIVATE=3, PUBLIC=2
      * @param key [out] key handle, null if not found
      * @return result
      * @retval 0 success
      * @retval 0x32 CKR_DEVICE_REMOVED
      * @retval 0xE0 CKR_TOKEN_NOT_PRESENT
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h) or OpenSSL eror code.
     */
    unsigned long GetKey(unsigned long session, unsigned char* id, unsigned long idLen, unsigned long type, void** key);
 
    /** @brief Free key handle
      * Free key handle
      * @param key [in] key handle
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h) or OpenSSL eror code.
     */
    unsigned long FreeKey(void* key);
 
    /** @brief Get key type
      * Get key type
      * @param key [in] key handle
      * @param type [out] RSA=0, EC=3
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to  OpenSSL eror code.
     */
    unsigned long GetKeyType(void* key, unsigned long* type);
 
    /** @brief Get number of certs
      * Get number of certs
      * @param session [in] session id
      * @param certNum [out] number of certs
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long GetCertNum(unsigned long session, unsigned long* certNum);
 
    /** @brief Get cert ID
      * Get cert ID
      * @param session [in] session id
      * @param certIndex  [in] index of cert
      * @param certID [out] ID of the cert
      * @param certIDLen [in, out] length of certID
      * @return result
      * @retval 0 success
      * @retval 0x10000007 ARGUMENTS_BAD
      * @retval 0x10000150 BUFFER_TOO_SMALL
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h)
     */
    unsigned long GetCertID(unsigned long session, unsigned long certIndex, unsigned char* certID, unsigned long* certIDLen);
 
    /** @brief Get cert handle by ID
      * Get cert handle by ID
      * @param session [in] session id
      * @param certID [in] ID of the cert
      * @param idLen [in] length of id
      * @param cert [out] cert handle
      * @return result
      * @retval 0 success
      * @retval 0x32 CKR_DEVICE_REMOVED
      * @retval 0xE0 CKR_TOKEN_NOT_PRESENT
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h) or OpenSSL eror code.
     */
    unsigned long GetCert(unsigned long session, unsigned char* certID, unsigned long idLen, void** cert);
 
    /** @brief Convert to cert
      * Convert der encoded data to Cert
      * @param der [in] der data
      * @param derLen [in] length of der
      * @param cert [out] cert handle, null if not found
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long DER2Cert(unsigned char* der, int derLen, void** cert);
 
    /** @brief Convert to der
      * Convert Cert to der encoded data
      * @param cert [in] cert handle
      * @param der [out] der data
      * @param derLen [in, out] length of der
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long Cert2DER(void* cert, unsigned char* der, int* derLen);
 
    /** @brief Free cert handle
      * Free cert handle
      * @param cert [in] cert handle
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h) or OpenSSL eror code.
     */
    unsigned long FreeCert(void* cert);
    //*****************Secure Element SDK *********************
 
    //*****************PKI Basic SDK *********************
    /** @brief basic signature  function
      * generate basic signature with specified private key
      * @param key [in] key handle
      * @param hashAlgorithm  [in] digest algorithm, such as "SHA256"
      * @param tbs  [in] to-be-signed data
      * @param tbsLen  [in] to-be-signed data length
      * @param signature  [out] signature
      * @param signatureLen  [in, out] signature length. If this value is less than the expected length, an error will be returned and signature_len will be written to the expected length.
      * @return result
      * @retval 0 success
      * @retval 0x70001XXX PKCS#11 C_Sign fail, XXX = pkcs11 CKR error code
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h) or OpenSSL eror code.
     */
    unsigned long Sign(void* key, const char* hashAlgorithm, unsigned char* tbs, int tbsLen, unsigned char* signature, int* signatureLen);
 
    /** @brief basic rsa decrypt function
      * decrypt rsa cipher with specified private key
      * @param key [in] key handle
      * @param cipher  [in] cipher data
      * @param cipherLen  [in] length of cipher
      * @param plain  [out] plain
      * @param plainLen  [in, out] length of plain
      * @return result
      * @retval 0 success
      * @retval 0x70003XXX PKCS#11 C_Decrypt fail, XXX = pkcs11 CKR error code
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h) or OpenSSL eror code.
     */
    unsigned long RsaDecrypt(void* key, unsigned char* cipher, int cipherLen, unsigned char* plain, int* plainLen);
 
    /** @brief signature (PKCS#7) function
      * generate signature(PKCS#7) with specified private key
      * @param key [in] key handle
      * @param signerCert  [in] signer cert handle
      * @param hashAlgorithm  [in] digest algorithm, such as "SHA256"
      * @param tbs  [in] to-be-signed data
      * @param tbsLen  [in] to-be-signed data length
      * @param signature  [out] signature
      * @param signatureLen  [in, out] signature length. If this value is less than the expected length, an error will be returned and signature_len will be written to the expected length.
      * @return result
      * @retval 0 success
      * @retval 0x70001XXX PKCS#11 C_Sign fail, XXX = pkcs11 CKR error code
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h) or OpenSSL eror code.
     */
    unsigned long SignPKCS7(void* key, void* signerCert, const char* hashAlgorithm, unsigned char* tbs, int tbsLen, unsigned char* signature, int* signatureLen);
 
    /** @brief decrypt PKCS#7 function
      * decrypt PKCS#7 enveloped data with specified private key
      * @param key [in] key handle
      * @param recepientCert [in] recepient cert handle
      * @param cipher  [in] cipher data
      * @param cipherLen  [in] length of cipher
      * @param plain  [out] plain
      * @param plainLen  [in, out] length of plain
      * @return result
      * @retval 0 success
      * @retval 0x70003XXX PKCS#11 C_Decrypt fail, XXX = pkcs11 CKR error code
      * @retval other_value fail, please refer to PKCS#11 error code(pkcs11t.h) or OpenSSL eror code.
     */
    unsigned long DecryptPKCS7(void* key, void* recepientCert, unsigned char* cipher, int cipherLen, unsigned char* plain, int* plainLen);
 
    /** @brief get cert serial number
      * get cert serial number
      * @param cert [in] cert handle
      * @param serialNumber  [out] plain
      * @param serialNumberLen  [in, out] length of serialNumber
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertSerialNumber(void* cert, unsigned char* serialNumber, int* serialNumberLen);
 
    /** @brief get cert subject name
      * get cert subject
      * @param cert [in] cert handle
      * @param LDAPType [in] 1 as LDAP, 0 for reverse
      * @param name  [out] subject name
      * @param nameLen  [in, out] length of name
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertSubject(void* cert, int LDAPType, char* name, int* nameLen);
 
    /** @brief get cert issuer name
      * get cert issuer
      * @param cert [in] cert handle
      * @param LDAPType [in] 1 as LDAP, 0 for reverse
      * @param name  [out] issuer name
      * @param nameLen  [in, out] length of name
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertIssuer(void* cert, int LDAPType, char* name, int* nameLen);
 
    /** @brief get cert notBefore time
      * get cert notBefore time
      * @param cert [in] cert handle
      * @param notBeforeDate  [out] notBefore (UTC)
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertNotBefore(void* cert, struct tm* notBeforeDate);
 
    /** @brief get cert notAfter time
      * get cert notAfter time
      * @param cert [in] cert handle
      * @param notAfterDate  [out] notAfter (UTC)
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertNotAfter(void* cert, struct tm* notAfterDate);
 
    /** @brief get cert public key
      * get cert public key
      * @param cert [in] cert handle
      * @param key  [out] public key handle
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertPublicKey(void* cert, void** key);
    //*****************PKI Basic SDK *********************
 
#ifdef __cplusplus
}
#endif
 
#endif
//_IOS_CHTSE_H




