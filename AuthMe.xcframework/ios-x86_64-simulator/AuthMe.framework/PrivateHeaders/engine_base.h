#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_Engine_Initial();

EAuthMeEngineReturnCode AuthMe_Engine_Release();

EAuthMeEngineReturnCode AuthMe_Engine_Authorization(const char* pToken);

EAuthMeEngineReturnCode AuthMe_Detector_Release(long handle);

#ifdef __cplusplus
}
#endif