#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_type_v3.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Initial(long handle, const AuthMeIDCardAntiFraudServiceModels* pParams);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_SetUIParams(long handle, const AuthMeV3ServiceUIParams* pParams);

AuthMeV3ServiceUIParams AuthMe_IDCardAntiFraudService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_SetParams(long handle, const AuthMeIDCardAntiFraudParams* pParams);

AuthMeIDCardAntiFraudParams AuthMe_IDCardAntiFraudService_GetParams(long handle);

AuthMeRectFloat AuthMe_IDCardAntiFraudService_GetNormalizedROI(long handle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_SetCardMatchNormalizedROI(long handle, const float* pPoints, int iLength);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Start(long handle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Run(long handle, AuthMeImage* pImage, AuthMeIDCardAntiFraudResult* pResult);

#ifdef __cplusplus
}
#endif