#ifndef _IOS_CHTSE_MOI_H
#define _IOS_CHTSE_MOI_H

#define IOS_CHTSE_MOI_VERSION                          0x01000000UL

#ifdef __cplusplus
extern "C" {
#endif

    /** @brief get GPKI Subject Type OID
      * get GPKI Subject Type OID
      * @param cert [in] cert handle
      * @param subjectTypeOID [out] subjectTypeOID, MOICA natural person = 2.16.886.1.100.3.1.1
      * @param subjectTypeOIDLen  [out] length of subjectTypeOID
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertSubjectTypeOID(void* cert, char* subjectTypeOID, int* subjectTypeOIDLen);

    /** @brief get GPKI Tail Of CitizenID
      * get Tail Of CitizenID
      * @param cert [in] cert handle
      * @param tailOfCitizenID [out] tail of citizenID
      * @param tailOfCitizenIDLen  [out] length of tailOfCitizenID
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertTailOfCitizenID(void* cert, char* tailOfCitizenID, int* tailOfCitizenIDLen);

    /** @brief get GPKI Subject Holder Rank
      * get  Subject Holder Rank
      * @param cert [in] cert handle
      * @param holderRank [out] holderRank, like primary or secondary, not present in normal MOICA card
      * @param holderRankLen  [out] length of holderRank
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to OpenSSL eror code.
     */
    unsigned long GetCertSubjectHolderRank(void* cert, char* holderRank, int* holderRankLen);

    /** @brief get PIN code retry remaining counter
      * get  PIN code retry remaining counter
      * @param session [in] session handle
      * @param counter [out] remaining counter, 1 = last chance, 0 = locked
      * @return result
      * @retval 0 success
      * @retval other_value fail, please refer to PKCS#11 eror code.
     */
    unsigned long GetRetryRemaining(unsigned long session, unsigned long *counter);

#ifdef __cplusplus
}
#endif

#endif
//_IOS_CHTSE_MOI_H


