#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_CardClassification_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_CardClassification_Initial(long handle, const char* szModelPath);

const char* AuthMe_CardClassification_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_CardClassification_Run(long handle, AuthMeImage* pImage, int* pPoints, int iLength, EAuthMeCardClass* peClass, AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif