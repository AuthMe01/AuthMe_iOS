#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_type_v3.h"

void AuthMe_ReleaseImage(AuthMeImage* pImage);

void GetFASStageName(EAuthMeFASServiceStage eStage, char* pBuffer, int iSize);

#ifdef __cplusplus
}
#endif