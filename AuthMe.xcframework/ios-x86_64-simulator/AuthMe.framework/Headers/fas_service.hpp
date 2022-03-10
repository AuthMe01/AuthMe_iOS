#pragma once
#include <string>
#include <vector>
#include "engine_type_v3.h"
#include "opencv2/core.hpp"

namespace AuthMe
{

class IFASService
{
    public:
        virtual ~IFASService() {}

        virtual bool Initial(const AuthMeFASServiceModels& params) = 0;

        virtual void SetUIParams(const AuthMeV3ServiceUIParams& params) = 0;

        virtual AuthMeV3ServiceUIParams GetUIParams() = 0;

        virtual void SetParams(const AuthMeFASParams& params) = 0;

        virtual AuthMeFASParams GetParams() = 0;

        // return a rect in normalized axis, i.e., l,t,w,h in range [0~1], representing previewPosition
        virtual cv::Rect2f GetNormalizedFaceROI() = 0;

        virtual void Start() = 0;

        virtual AuthMeFASResult Run(const cv::Mat& inputImage)  = 0;
};

IFASService* CreateFASService_Passive();

IFASService* CreateFASService_Active();

}
