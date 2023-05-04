#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_CardOCRService_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum);

EAuthMeEngineReturnCode AuthMe_CardOCRService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_CardOCRService_Initial(long handle, const AuthMeCardOCRModels* pParams);

EAuthMeEngineReturnCode AuthMe_CardOCRService_SetUIParams(long handle, const AuthMeServiceUIParams* pParams);

AuthMeServiceUIParams AuthMe_CardOCRService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_CardOCRService_SetParams(long handle, const AuthMeCardOCRParams* pParams);

AuthMeCardOCRParams AuthMe_CardOCRService_GetParams(long handle);

AuthMeRectFloat AuthMe_CardOCRService_GetAnalysisROI(long handle);

EAuthMeEngineReturnCode AuthMe_CardOCRService_SetCardMatchROI(long handle, const float* pPoints, int iLength);

EAuthMeEngineReturnCode AuthMe_CardOCRService_SetOption(long handle, const char* pOption, const char* pValue);

const char* AuthMe_CardOCRService_GetOption(long handle, const char* pOption);

EAuthMeEngineReturnCode AuthMe_CardOCRService_Start(long handle);

// need to call AuthMe_ReleaseImage in service_utility.h for pResult->image after use
EAuthMeEngineReturnCode AuthMe_CardOCRService_Run(long handle, const AuthMeImage* pImage, AuthMeCardOCRResult* pResult);

EAuthMeEngineReturnCode AuthMe_CardOCRService_Stop(long handle);

AuthMeEngineDebugInfoList AuthMe_CardOCRService_GetDebugInfo(long handle);

EAuthMeEngineReturnCode AuthMe_CardOCRService_GetDebugImage(long handle, AuthMeImage* pImage);

const char* AuthMe_CardOCRService_GetJsonReport(long handle);

#ifdef __cplusplus
}
#endif
