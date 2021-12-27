#ifndef ios_chtse_apdu_h
#define ios_chtse_apdu_h

#define IOS_CHTSE_APDU_VERSION                          0x01000000UL
    /** @brief get APDU counter
      * get APDU counter (count since C_Initialize)
      * @param session [in] session handle
      * @param counter [out] APDU counter
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 eror code.
     */
unsigned long GetApduCounter(unsigned long session, unsigned long* counter);

#endif /* ios_chtse_apdu_h */
