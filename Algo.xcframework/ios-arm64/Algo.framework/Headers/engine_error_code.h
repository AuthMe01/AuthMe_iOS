#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _E_AUTHME_ENGINE_RETUEN_CODE : int
{
    eAuthMe_Engine_Success = 0,
    eAuthMe_Engine_Failed,
    eAuthMe_Engine_VersionNotSupported,
    eAuthMe_Engine_Authorization_Pass,
    eAuthMe_Engine_Authorization_Failed,
} EAuthMeEngineReturnCode;

#ifdef __cplusplus
}
#endif
