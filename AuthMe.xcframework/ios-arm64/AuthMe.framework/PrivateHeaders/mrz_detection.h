#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_MRZDetection_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_MRZDetection_Initial(long handle, const char* szModelPath);

const char* AuthMe_MRZDetection_GetModelInfo(long handle);

// pPosition should be a pointer to array with length = 8 (x1, y1, x2, y2, ...), or NULL if use whole image
// need to delete *ppPoints after use
EAuthMeEngineReturnCode AuthMe_MRZDetection_Detect(long handle, AuthMeImage* pImage, const int* pPosition, int iPosLength, float** ppPoints, int* piLength, AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif