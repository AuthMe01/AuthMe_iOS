#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_type_v3.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_CardOCR_GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum);

EAuthMeEngineReturnCode AuthMe_CardOCR_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_CardOCR_Initial(long handle, const AuthMeCardOCRModels* pParams);

EAuthMeEngineReturnCode AuthMe_CardOCR_SetUIParams(long handle, const AuthMeV3ServiceUIParams* pParams);

AuthMeV3ServiceUIParams AuthMe_CardOCR_GetUIParams(long handle);

EAuthMeEngineReturnCode AuthMe_CardOCR_SetParams(long handle, const AuthMeCardOCRParams* pParams);

AuthMeCardOCRParams AuthMe_CardOCR_GetParams(long handle);

AuthMeRectFloat AuthMe_CardOCR_GetNormalizedROI(long handle);

EAuthMeEngineReturnCode AuthMe_CardOCR_SetCardMatchNormalizedROI(long handle, const float* pPoints, int iLength);

// set customized roi for reflection detection, ROI t,l,b,r range [0~1]
// restore to default by setting empty array
EAuthMeEngineReturnCode AuthMe_CardOCR_SetCustomReflectiveROI(long handle, const AuthMeRectFloat* pRect, int iLength);

// need to call AuthMe_ReleaseImage in utility_v3.h for pResult->image after use
EAuthMeEngineReturnCode AuthMe_CardOCR_Run(long handle, const AuthMeImage* pImage, AuthMeCardOCRResult* pResult);

#ifdef __cplusplus
}
#endif
