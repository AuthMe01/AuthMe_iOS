#pragma once
#include <string>
#include <vector>
#include "engine_service_type.h"
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "card_detection.hpp"
#include "card_classification.hpp"
#include "laser_tag_detection.hpp"
#include "taiwan_hole_detection.hpp"
#include "metal_tag_detection.hpp"
#include "reflection_detection.hpp"

namespace AuthMe
{

class IIDCardAntiFraudService : public IEngineBase
{
    public:
        virtual ~IIDCardAntiFraudService() {}

        static std::vector<AuthMeModelVersion> GetModelVersion();

        virtual const std::vector<AuthMeEngineDebugInfo> &GetDeBugInfo() = 0;

        virtual bool Initial(const AuthMeIDCardAntiFraudServiceModels& models) = 0;

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