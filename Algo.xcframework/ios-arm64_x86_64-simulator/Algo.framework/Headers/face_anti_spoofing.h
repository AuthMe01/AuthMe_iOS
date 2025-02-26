#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_FaceAntiSpoofing_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_FaceAntiSpoofing_Initial(long handle, const char* szModelPath);

const char* AuthMe_FaceAntiSpoofing_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_FaceAntiSpoofing_SetThreshold(long handle, float fThreshold);

float AuthMe_FaceAntiSpoofing_GetThreshold(long handle);

EAuthMeEngineReturnCode AuthMe_FaceAntiSpoofing_SetMinFrameNum(long handle, int iLength);

int AuthMe_FaceAntiSpoofing_GetMinFrameNum(long handle);

EAuthMeEngineReturnCode AuthMe_FaceAntiSpoofing_Reset(long handle);

EAuthMeEngineReturnCode AuthMe_FaceAntiSpoofing_Run(long handle,
        AuthMeImage* pImage,
        const float* pPoints,
        int iLength,
        AuthMeFASModuleOutput* pOutput,
        AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif