#pragma once
#include "engine_type_v3.h"
#include "opencv2/core.hpp"

namespace AuthMe
{

void ReleaseImage(AuthMeImage& image);

AuthMeImage AllocateImage(const cv::Mat& matImage, EAuthMeColorFormat eFormat);

std::string GetEnumName(EAuthMeFASServiceStage eStage);

}
