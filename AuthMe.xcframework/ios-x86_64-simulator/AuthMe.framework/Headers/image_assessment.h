#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "engine_error_code.h"
#include "engine_type.h"
#include "engine_base.h"

/// default setting: iAnalyzeWidth = 256, iAnalyzeHeight = 256, bAdjust = true
float AuthMe_ImageSharpness(const AuthMeImage *pImage, int iAnalyzeWidth, int iAnalyzeHeight, bool bAdjust);

float AuthMe_ImageReflective(const AuthMeImage *pImage);

float AuthMe_CheckIDCardFrontColor(AuthMeImage* pImage);

float AuthMe_CheckIDCardFrontColor_Polygon(AuthMeImage* pImage, int *pPoints, int iLength);

// set **ppMetalTagPosition and *piPosLength if needed, otherwise NULL
EAuthMeIDCardMetalTagStatus AuthMe_IDCardMetalTagDetect(const AuthMeImage *pImage, int **ppMetalTagPosition, int *piPosLength);

// set **ppMetalTagPosition and *piPosLength if needed, otherwise NULL
EAuthMeIDCardMetalTagStatus AuthMe_IDCardMetalTagDetect_Polygon(const AuthMeImage *pImage,
        const int *pPoints,
        const int iLength,
        int **ppMetalTagPosition,
        int *piPosLength);


#ifdef __cplusplus
}
#endif