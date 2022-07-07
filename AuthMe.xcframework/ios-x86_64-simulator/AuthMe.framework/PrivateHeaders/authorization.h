#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"

EAuthMeSDKAuthStatus AuthMe_VerifySDK(const char* pServiceCrt, const char* pToken);

#ifdef __cplusplus
}
#endif