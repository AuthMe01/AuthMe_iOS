#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_FaceAlignment_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_FaceAlignment_Initial(long handle, const char* szModelPath);

const char* AuthMe_FaceAlignment_GetModelInfo(long handle);

// need to delete *ppPoints after use
EAuthMeEngineReturnCode AuthMe_FaceAlignment_Run(long handle,
        const AuthMeImage* pImage,
        const AuthMeRectFloat* pFaceRect,
        float **ppPoints,
        int* piLength,
        AuthMeEngineDebugInfo* pDebugInfo);

#define DEFAULT_EYE_THRESHOLD 0.2f
EAuthMeEngineReturnCode AuthMe_FaceAlignment_GetEyeStatus(const float *pPoints,
        const int iLength,
        float *pfScore,
        EAuthMeEyeStatus* peStatus,
        float fThreshold);

#define DEFAULT_MOUTH_THRESHOLD 0.5f
EAuthMeEngineReturnCode AuthMe_FaceAlignment_GetMouthStatus(const float *pPoints,
        const int iLength,
        float *pfScore,
        EAuthMeMouthStatus* peStatus,
        float fThreshold);

#ifdef __cplusplus
}
#endif