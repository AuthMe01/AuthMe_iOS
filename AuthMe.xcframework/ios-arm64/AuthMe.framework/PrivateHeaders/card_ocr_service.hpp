#pragma once
#include "engine_service_type.h"
#include "opencv2/core.hpp"
#include "engine_base.hpp"

namespace AuthMe
{

class ICardOCRService : public IEngineBase
{
    public:
        virtual ~ICardOCRService() {}

        static std::vector<AuthMeModelVersion> GetModelVersion();

        virtual const std::vector<AuthMeEngineDebugInfo> &GetDeBugInfo() = 0;

        virtual bool Initial(const AuthMeCardOCRModels& models) = 0;

        virtual void SetUIParams(const AuthMeServiceUIParams& params) = 0;

        virtual AuthMeServiceUIParams GetUIParams() const = 0;

        virtual void SetParams(const AuthMeCardOCRParams& params) = 0;

        virtual AuthMeCardOCRParams GetParams() const = 0;

        // return ROI of image analysis, l,t,w,h in range [0~1], representing previewPosition
        virtual cv::Rect2f GetAnalysisROI() const = 0;

        // points in vecVertices should be clockwise or counterclockwise
        // point x,y range in [0~1], representing previewPosition
        // will reset card match status in AuthMeIDCardAntiFraudResult after SetCardMatchROI()
        virtual void SetCardMatchROI(const std::vector<cv::Point2f>& vecVertices) = 0;

        virtual void EnableAlgoLog(bool enable) = 0;

        virtual EAuthMeEngineReturnCode Start() = 0;

        virtual AuthMeCardOCRResult Run(const cv::Mat& srcImage) = 0;

        virtual EAuthMeEngineReturnCode Stop() = 0;

        virtual const std::string& GetJsonReport() = 0;

        virtual EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) = 0;

};


ICardOCRService* CreateCardOCRService();

}
