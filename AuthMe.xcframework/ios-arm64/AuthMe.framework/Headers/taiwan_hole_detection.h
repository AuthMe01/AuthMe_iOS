#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_TaiwanHoleDetection_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_TaiwanHoleDetection_Initial(long handle, const char* szModelPath);

const char* AuthMe_TaiwanHoleDetection_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_TaiwanHoleDetection_SetThreshold(long handle, float fThreshold);

EAuthMeEngineReturnCode AuthMe_TaiwanHoleDetection_Detect(long handle,
        AuthMeImage* pImage,
        const int *pPoints,
        const int iLength,
        EAuthMeTaiwanHoleStatus* peStatus,
        AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif