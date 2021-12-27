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

// need to delete *ppPoints after use
EAuthMeEngineReturnCode AuthMe_MRZDetection_Detect(long handle, AuthMeImage* pImage, float** ppPoints, int* piLength, AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif