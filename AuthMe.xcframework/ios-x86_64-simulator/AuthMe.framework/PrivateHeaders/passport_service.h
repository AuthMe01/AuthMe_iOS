#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_PassportService_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum);

EAuthMeEngineReturnCode AuthMe_PassportService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_PassportService_Initial(long handle, const AuthMePassportServiceModels* pParams);

EAuthMeEngineReturnCode AuthMe_PassportService_SetUIParams(long handle, const AuthMeServiceUIParams* pParams);

AuthMeServiceUIParams AuthMe_PassportService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_PassportService_SetParams(long handle, const AuthMePassportServiceParams* pParams);

AuthMePassportServiceParams AuthMe_PassportService_GetParams(long handle);

EAuthMeEngineReturnCode AuthMe_PassportService_SetMatchROI(long handle, const float* pPoints, int iLength);

// returns a float[8] array pointer
const float* AuthMe_PassportService_GetMatchROI(long handle);

EAuthMeEngineReturnCode AuthMe_PassportService_EnableAlgoLog(long handle, int enable);

EAuthMeEngineReturnCode AuthMe_PassportService_Start(long handle);

EAuthMeEngineReturnCode AuthMe_PassportService_Run(long handle, const AuthMeImage* pImage, AuthMePassportServiceResult* pResult);

EAuthMeEngineReturnCode AuthMe_PassportService_Stop(long handle);

AuthMeEngineDebugInfoList AuthMe_PassportService_GetDebugInfo(long handle);

EAuthMeEngineReturnCode AuthMe_PassportService_GetDebugImage(long handle, AuthMeImage* pImage);

const char* AuthMe_PassportService_GetJsonReport(long handle);

AuthMeMRZFieldTD3 AuthMe_PassportService_GetFinalResult(long handle);

// need to call free()
EAuthMeEngineReturnCode AuthMe_PassportService_ToJson(const AuthMeMRZFieldTD3* pField, char **ppJson);

#ifdef __cplusplus
}
#endif
