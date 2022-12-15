#pragma once
#include "engine_type_v3.h"
#include "opencv2/core.hpp"
#include "engine_base.hpp"

namespace AuthMe
{

class ICardOCR : public IEngineBase
{
    public:
        virtual ~ICardOCR() {}

        virtual bool Initial(const AuthMeCardOCRModels& params) = 0;

        virtual void SetUIParams(const AuthMeV3ServiceUIParams& params) = 0;

        virtual AuthMeV3ServiceUIParams GetUIParams() const = 0;

        virtual void SetParams(const AuthMeCardOCRParams& params) = 0;

        virtual AuthMeCardOCRParams GetParams() const = 0;

        // return ROI of image analysis, l,t,w,h in range [0~1], representing previewPosition
        virtual cv::Rect2f GetNormalizedROI() const = 0;

        // set customized roi for reflection detection, ROI x,y,w,h range [0~1]
        // restore to default by setting empty vector
        virtual void SetCustomReflectiveROI(const std::vector<cv::Rect2f>& vecROI) = 0;

        // points in vecVertices should be clockwise or counterclockwise
        // point x,y range in [0~1], representing previewPosition
        // will reset card match status in AuthMeIDCardAntiFraudResult after SetCardMatchROI()
        virtual void SetCardMatchNormalizedROI(const std::vector<cv::Point2f>& vecVertices) = 0;

        virtual AuthMeCardOCRResult Run(const cv::Mat& srcImage) = 0;

};


ICardOCR* CreateCardOCR();

}
