#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Initial(long handle, const AuthMeIDCardAntiFraudServiceModels* pParams);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_SetUIParams(long handle, const AuthMeServiceUIParams* pParams);

AuthMeServiceUIParams AuthMe_IDCardAntiFraudService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_SetParams(long handle, const AuthMeIDCardAntiFraudParams* pParams);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_SetStage(long handle, const EAuthMeIDCardAntiFraudStage* pStage, int iStageNum);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_GetStage(long handle, EAuthMeIDCardAntiFraudStage** ppStage, int* piStageNum);

AuthMeIDCardAntiFraudParams AuthMe_IDCardAntiFraudService_GetParams(long handle);

AuthMeRectFloat AuthMe_IDCardAntiFraudService_GetAnalysisROI(long handle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_SetFrontalCardVertices(long handle, const float* pPoints, int iLength);

// returns a float[8] array pointer
const float* AuthMe_IDCardAntiFraudService_GetCardMatchROI(long handle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_EnableAlgoLog(long handle, int enable);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Start(long handle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Run(long handle, AuthMeImage* pImage, AuthMeIDCardAntiFraudResult* pResult);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_Stop(long handle);

AuthMeEngineDebugInfoList AuthMe_IDCardAntiFraudService_GetDebugInfo(long handle);

EAuthMeEngineReturnCode AuthMe_IDCardAntiFraudService_GetDebugImage(long handle, AuthMeImage* pImage);

const char* AuthMe_IDCardAntiFraudService_GetJsonReport(long handle);

#ifdef __cplusplus
}
#endif