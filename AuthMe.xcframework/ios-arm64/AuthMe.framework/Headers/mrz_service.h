#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

EAuthMeEngineReturnCode AuthMe_MRZService_Create(long* pHandle);

EAuthMeEngineReturnCode AuthMe_MRZService_Initial(long handle, const char* szDetModelPath, const char* szRegModelPath);

const char* AuthMe_MRZService_GetModelInfo(long handle);

EAuthMeEngineReturnCode AuthMe_MRZService_Run(long handle,
        AuthMeImage* pImage,
        EAuthMeMRZRecogStatus *peStatus,
        AuthMeMRZFieldTD3 *pField,
        float** ppPoints,
        int* piLength,
        AuthMeEngineDebugInfo aDebugInfo[2]);

#ifdef __cplusplus
}
#endif