#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_Detector_Release(long handle, const char* verifyCode);

#ifdef __cplusplus
}
#endif