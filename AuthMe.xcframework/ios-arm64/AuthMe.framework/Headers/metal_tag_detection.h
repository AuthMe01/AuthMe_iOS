#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_MetalTagDetection_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_MetalTagDetection_Initial(long handle, const char* szModelPath);

const char* AuthMe_MetalTagDetection_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_MetalTagDetection_SetThreshold(long handle, float fThreshold);

float AuthMe_MetalTagDetection_GetThreshold(long handle);

// length of ppPoints = *piResultNum * 4 (2 pts per tag)
// need to delete[] pVertices and ppPoints
EAuthMeEngineReturnCode AuthMe_MetalTagDetection_Detect(long handle,
        const AuthMeImage* pImage,
        const int *pVertices,
        const int iLength,
        EAuthMeIDCardMetalTagStatus** ppeStatus,
        int **ppPoints,
        int *piResultNum,
        AuthMeEngineDebugInfo* pDebugInfo);


#ifdef __cplusplus
}
#endif