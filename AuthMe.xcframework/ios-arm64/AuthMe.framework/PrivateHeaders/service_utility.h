#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_service_type.h"

void AuthMe_ReleaseImage(AuthMeImage* pImage);

long AuthMe_CreateModel(const char* modelName, const char* modelPath);

void AuthMe_ReleaseModel(long model);

#ifdef __cplusplus
}
#endif