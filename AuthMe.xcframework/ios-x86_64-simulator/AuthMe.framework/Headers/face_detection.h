#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_FaceDetection_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_FaceDetection_Initial(long handle, const char* szModelPath);

const char* AuthMe_FaceDetection_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_FaceDetection_SetThreshold(long handle, float fThreshold);

// need to delete *ppFaceInfo after use
EAuthMeEngineReturnCode AuthMe_FaceDetection_Detect(long handle, AuthMeImage* pImage, AuthMeFaceInfo **ppFaceInfo, int* piLength, AuthMeEngineDebugInfo* pDebugInfo);

EAuthMeFacePose AuthMe_GetFacePose(const float* pfLandmarks, const int iLength);

#ifdef __cplusplus
}
#endif