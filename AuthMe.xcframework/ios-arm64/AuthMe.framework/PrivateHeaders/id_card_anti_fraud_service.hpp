#pragma once
#include <string>
#include <vector>
#include "engine_type_v3.h"
#include "opencv2/core.hpp"
#include "engine_base.hpp"

namespace AuthMe
{

class IIDCardAntiFraudService : public IEngineBase
{
    public:
        virtual ~IIDCardAntiFraudService() {}

        virtual bool Initial(const AuthMeIDCardAntiFraudServiceModels& params) = 0;

        virtual void SetUIParams(const AuthMeV3ServiceUIParams& params) = 0;

        virtual AuthMeV3ServiceUIParams GetUIParams() const = 0;

        virtual void SetParams(const AuthMeIDCardAntiFraudParams& params) = 0;

        virtual AuthMeIDCardAntiFraudParams GetParams() const = 0;

        // return ROI of image analysis, l,t,w,h in range [0~1], representing previewPosition
        virtual cv::Rect2f GetNormalizedROI() const = 0;

        // points in vecVertices should be clockwise or counterclockwise
        // point x,y range in [0~1], representing previewPosition
        // will reset card match status in AuthMeIDCardAntiFraudResult after SetCardMatchROI()
        virtual void SetCardMatchNormalizedROI(const std::vector<cv::Point2f>& vecVertices) = 0;

        virtual void Start() = 0;

        virtual AuthMeIDCardAntiFraudResult Run(const cv::Mat& srcImage) = 0;
};

IIDCardAntiFraudService* CreateIDCardAntiFraudService();

}