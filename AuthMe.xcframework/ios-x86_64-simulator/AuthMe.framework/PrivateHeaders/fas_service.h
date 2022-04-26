#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_type_v3.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_FASService_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum);

EAuthMeEngineReturnCode AuthMe_FASServicePassive_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_FASServiceActive_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_FASService_Initial(long handle, const AuthMeFASServiceModels* pParams);

EAuthMeEngineReturnCode AuthMe_FASService_SetUIParams(long handle, const AuthMeV3ServiceUIParams* pParams);

AuthMeV3ServiceUIParams AuthMe_FASService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_FASService_SetParams(long handle, const AuthMeFASParams* pParams);

AuthMeFASParams AuthMe_FASService_GetParams(long handle);

AuthMeRectFloat AuthMe_FASService_GetNormalizedFaceROI(long handle);

EAuthMeEngineReturnCode AuthMe_FASService_Start(long handle);

EAuthMeEngineReturnCode AuthMe_FASService_Run(long handle, AuthMeImage* pImage, AuthMeFASResult* pResult);

#ifdef __cplusplus
}
#endif