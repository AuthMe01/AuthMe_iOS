#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"
#include "engine_error_code.h"
#include "card_detection.h"
#include "card_classification.h"
#include "reflection_detection.h"

EAuthMeEngineReturnCode AuthMe_CardOCRService_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum);

EAuthMeEngineReturnCode AuthMe_CardOCRService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_CardOCRService_Initial(long handle, const AuthMeCardOCRModels* pParams);

EAuthMeEngineReturnCode AuthMe_CardOCRService_SetUIParams(long handle, const AuthMeV3ServiceUIParams* pParams);

AuthMeV3ServiceUIParams AuthMe_CardOCRService_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_CardOCRService_SetParams(long handle, const AuthMeCardOCRParams* pParams);

AuthMeCardOCRParams AuthMe_CardOCRService_GetParams(long handle);

AuthMeRectFloat AuthMe_CardOCRService_GetNormalizedROI(long handle);

EAuthMeEngineReturnCode AuthMe_CardOCRService_SetCardMatchNormalizedROI(long handle, const float* pPoints, int iLength);

// set customized roi for reflection detection, ROI t,l,b,r range [0~1]
// restore to default by setting empty array
EAuthMeEngineReturnCode AuthMe_CardOCRService_SetCustomReflectiveROI(long handle, const AuthMeRectFloat* pRect, int iLength);

// need to call AuthMe_ReleaseImage in service_utility.h for pResult->image after use
EAuthMeEngineReturnCode AuthMe_CardOCRService_Run(long handle, const AuthMeImage* pImage, AuthMeCardOCRResult* pResult);

AuthMeEngineDebugInfoList AuthMe_CardOCRService_GetDebugInfo(long handle);

EAuthMeEngineReturnCode AuthMe_CardOCRService_GetDebugImage(long handle, AuthMeImage* pImage);

#ifdef __cplusplus
}
#endif
