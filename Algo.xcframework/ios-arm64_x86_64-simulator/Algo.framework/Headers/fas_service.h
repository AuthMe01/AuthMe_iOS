#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_FASService_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum);

EAuthMeEngineReturnCode AuthMe_FASService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_FASService_Initial(long handle, const AuthMeFASServiceModels* pParams);

EAuthMeEngineReturnCode AuthMe_FASService_SetUIParams(long handle, const AuthMeServiceUIParams* pParams);

AuthMeServiceUIParams AuthMe_FASService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_FASService_SetParams(long handle, const AuthMeFASParams* pParams);

AuthMeFASParams AuthMe_FASService_GetParams(long handle);

AuthMeRectFloat AuthMe_FASService_GetNormalizedFaceROI(long handle);

EAuthMeEngineReturnCode AuthMe_FASService_SetStage(long handle, const EAuthMeFASServiceStage* pStage, int iStageNum);

EAuthMeEngineReturnCode AuthMe_FASService_GetStage(long handle, EAuthMeFASServiceStage** ppStage, int* piStageNum);

EAuthMeEngineReturnCode AuthMe_FASService_SetStageParams(long handle, const AuthMeFASStageParams* pParams, int iIndex);

AuthMeFASStageParams AuthMe_FASService_GetStageParams(long handle, int iIndex);

EAuthMeEngineReturnCode AuthMe_FASService_SetOption(long handle, const char* pOption, const char* pValue);

const char* AuthMe_FASService_GetOption(long handle, const char* pOption);

EAuthMeEngineReturnCode AuthMe_FASService_Start(long handle);

EAuthMeEngineReturnCode AuthMe_FASService_Run(long handle, AuthMeImage* pImage, AuthMeFASResult* pResult);

EAuthMeEngineReturnCode AuthMe_FASService_RunWithDepth(long handle, AuthMeImage* pImage, AuthMeFASResult* pResult, AuthMeImage* pDepthImage, EAuthMePlatform* platform);

EAuthMeEngineReturnCode AuthMe_FASService_Stop(long handle);

AuthMeEngineDebugInfoList AuthMe_FASService_GetDebugInfo(long handle);

EAuthMeEngineReturnCode AuthMe_FASService_GetDebugImage(long handle, AuthMeImage* pImage);

const char* AuthMe_FASService_GetJsonReport(long handle);

#ifdef __cplusplus
}
#endif