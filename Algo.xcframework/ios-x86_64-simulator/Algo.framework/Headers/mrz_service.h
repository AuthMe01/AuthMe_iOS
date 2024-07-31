#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_MRZService_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum, EAuthMeMRZType eMRZType);

EAuthMeEngineReturnCode AuthMe_MRZService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_MRZService_Initial(long handle, const AuthMeMRZServiceModels* pParams);

EAuthMeEngineReturnCode AuthMe_MRZService_SetUIParams(long handle, const AuthMeServiceUIParams* pParams);

AuthMeServiceUIParams AuthMe_MRZService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_SetParams(long handle, const AuthMeMRZServiceParams* pParams);

AuthMeMRZServiceParams AuthMe_MRZService_GetParams(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_SetMatchROI(long handle, const float* pPoints, int iLength);

// returns a float[8] array pointer
const float* AuthMe_MRZService_GetMatchROI(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_SetOption(long handle, const char* pOption, const char* pValue);

const char* AuthMe_MRZService_GetOption(long handle, const char* pOption);

EAuthMeEngineReturnCode AuthMe_MRZService_Start(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_Run(long handle, const AuthMeImage* pImage, AuthMeMRZServiceResult* pResult);

EAuthMeEngineReturnCode AuthMe_MRZService_Stop(long handle);

AuthMeEngineDebugInfoList AuthMe_MRZService_GetDebugInfo(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_GetDebugImage(long handle, AuthMeImage* pImage);

const char* AuthMe_MRZService_GetJsonReport(long handle);

AuthMeMRZField AuthMe_MRZService_GetFinalResult(long handle);

// need to call free()
EAuthMeEngineReturnCode AuthMe_MRZService_ToJson(const AuthMeMRZField* pField, char **ppJson);

#ifdef __cplusplus
}
#endif
