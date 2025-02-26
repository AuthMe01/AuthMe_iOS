#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"
#include "engine_error_code.h"

// set pStatus, pfScore to nullptr if you don't need
// length of pPoint1, pPoint2 should be iPointNum*2
// pStatus, pfScore should be pre-allocated arrays, length = iPointNum
EAuthMeEngineReturnCode AuthMe_PointMatch(const float* pPoint1,
        const float* pPoint2,
        EAuthMeCardMatchStatus* pStatus,
        float* pfScore,
        const int iPointNum,
        const AuthMeSize imageSize,
        const float fThreshold);

// set pStatus, pfScore to nullptr if you don't need
// output only 1 status & score, not array
EAuthMeEngineReturnCode AuthMe_DIOUMatch(const float* pPoint1,
        const float* pPoint2,
        const int iPointNum,
        EAuthMeCardMatchStatus* pStatus,
        float* pfScore,
        const AuthMeSize imageSize,
        const float fThreshold);

#ifdef __cplusplus
}
#endif