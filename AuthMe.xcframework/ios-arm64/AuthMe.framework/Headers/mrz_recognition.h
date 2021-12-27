#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_MRZRecognition_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_MRZRecognition_Initial(long handle, const char* szModelPath);

const char* AuthMe_MRZRecognition_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_MRZRecognition_Run(long handle,
        AuthMeImage* pImage,
        float* pPoints,
        int iLength,
        EAuthMeMRZRecogStatus *peStatus,
        AuthMeMRZFieldTD3 *pField,
        AuthMeEngineDebugInfo* pDebugInfo);

#ifdef __cplusplus
}
#endif