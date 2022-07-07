#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"


EAuthMeEngineReturnCode AuthMe_MiniFAS_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_MiniFAS_Initial(long handle, const char* szModelPath);

const char* AuthMe_MiniFAS_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_MiniFAS_SetThreshold(long handle, float fThreshold);

float AuthMe_MiniFAS_GetThreshold(long handle);

EAuthMeEngineReturnCode AuthMe_MiniFAS_Run(long handle,
        const AuthMeImage* pImage,
        const AuthMeRectFloat* pFaceRect,
        EAuthMeFaceAntiSpoofingStatus *pStatus,
        float* pfScore,
        AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif
