#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_ReflectionDetection_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_ReflectionDetection_Initial(long handle, const char* szModelPath);

const char* AuthMe_ReflectionDetection_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_ReflectionDetection_SetThreshold(long handle, float fThreshold);

float AuthMe_ReflectionDetection_GetThreshold(long handle);

// set pVertices = NULL, iLength = 0 if using whole image
// set pROI = NULL, iRoiNum = 0 if using whole image
EAuthMeEngineReturnCode AuthMe_ReflectionDetection_Detect(long handle,
        const AuthMeImage* pImage,
        const int *pVertices,
        const int iLength,
        const AuthMeRectFloat *pROI,
        const int iRoiNum,
        float *pfScore,
        AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif
