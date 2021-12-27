#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_LaserTagDetection_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_LaserTagDetection_Initial(long handle, const char* szModelPath);

const char* AuthMe_LaserTagDetection_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_LaserTagDetection_SetThreshold(long handle, float fThreshold);

EAuthMeEngineReturnCode AuthMe_LaserTagDetection_Detect(long handle, AuthMeImage* pImage, int *pPoints, int iLength, EAuthMeLaserTagStatus* peStatus, AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif