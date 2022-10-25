#pragma once
#include "engine_service_type.h"
#include "opencv2/core.hpp"

namespace AuthMe
{

void ReleaseImage(AuthMeImage& image);

AuthMeImage AllocateImage(const cv::Mat& matImage, EAuthMeColorFormat eFormat);

long CreateModel(std::string modelName, std:: string modelPath);

void ReleaseModel(long model);

std::string GetEnumName(EAuthMeFASServiceStage eStage);

std::string GetEnumName(EAuthMeFASServiceStatus eStatus);

std::string GetEnumName(EAuthMeCardOCRStatus eStatus);

std::string GetEnumName(EAuthMeCardClass eClass);

std::string GetEnumName(EAuthMeIDCardAntiFraudStage eStage);

std::string GetEnumName(EAuthMeIDCardAntiFraudStatus eStatus);

std::string GetEnumName(EAuthMeCardMatchStatus eStatus);

std::string GetEnumName(EAuthMePassportServiceStatus eStatus);

}
