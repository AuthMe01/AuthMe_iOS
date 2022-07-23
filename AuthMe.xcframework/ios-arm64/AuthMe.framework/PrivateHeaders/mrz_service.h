#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"
#include "engine_error_code.h"
#include "mrz_detection.h"
#include "mrz_recognition.h"

EAuthMeEngineReturnCode AuthMe_MRZService_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum);

EAuthMeEngineReturnCode AuthMe_MRZService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_MRZService_Initial(long handle, const AuthMeMRZModels* pParams);

EAuthMeEngineReturnCode AuthMe_MRZService_SetUIParams(long handle, const AuthMeV3ServiceUIParams* pParams);

AuthMeV3ServiceUIParams AuthMe_MRZService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_SetParams(long handle, const AuthMeMRZParams* pParams);

AuthMeMRZParams AuthMe_MRZService_GetParams(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_Run(long handle, const AuthMeImage* pImage, AuthMeMRZResult* pResult);

AuthMeEngineDebugInfoList AuthMe_MRZService_GetDebugInfo(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_GetDebugImage(long handle, AuthMeImage* pImage);

#ifdef __cplusplus
}
#endif
