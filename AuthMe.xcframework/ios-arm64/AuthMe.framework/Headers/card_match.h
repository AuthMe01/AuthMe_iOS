#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "v3/engine_type_v3.h"
#include "engine_error_code.h"

EAuthMeEngineReturnCode AuthMe_PointMatch(const float* pPoint1,
        const float* pPoint2,
        EAuthMeCardMatchStatus* pStatus,
        const int iPointNum,
        const AuthMeSize imageSize,
        const float fThreshold);


EAuthMeCardMatchStatus AuthMe_DIOUMatch(const float* pPoint1,
                                        const float* pPoint2,
                                        const int iPointNum,
                                        const AuthMeSize imageSize,
                                        const float fThreshold);

#ifdef __cplusplus
}
#endif