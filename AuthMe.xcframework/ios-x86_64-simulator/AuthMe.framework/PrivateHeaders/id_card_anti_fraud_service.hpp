#pragma once
#include <string>
#include <vector>
#include "engine_service_type.h"
#include "opencv2/core.hpp"
#include "engine_base.hpp"

namespace AuthMe
{

class IIDCardAntiFraudService : public IEngineBase
{
    public:
        virtual ~IIDCardAntiFraudService() {}

        static std::vector<AuthMeModelVersion> GetModelVersion();

        virtual const std::vector<AuthMeEngineDebugInfo> &GetDeBugInfo() = 0;

        virtual bool Initial(const AuthMeIDCardAntiFraudServiceModels& models) = 0;

        virtual void SetUIParams(const AuthMeServiceUIParams& params) = 0;

        virtual AuthMeServiceUIParams GetUIParams() const = 0;

        virtual void SetParams(const AuthMeIDCardAntiFraudParams& params) = 0;

        virtual AuthMeIDCardAntiFraudParams GetParams() const = 0;

        virtual void SetStage(const std::vector<EAuthMeIDCardAntiFraudStage>& vecStage) = 0;

        virtual std::vector<EAuthMeIDCardAntiFraudStage> GetStage() const = 0;

        // return ROI of image analysis, l,t,w,h in range [0~1], representing previewPosition
        virtual cv::Rect2f GetAnalysisROI() const = 0;

        // points in vecVertices should be clockwise or counterclockwise
        // point x,y range in [0~1], representing previewPosition
        // will reset card match status in AuthMeIDCardAntiFraudResult after SetFrontalCardVertices()
        virtual void SetFrontalCardVertices(const std::vector<cv::Point2f>& vecVertices) = 0;

        virtual std::vector<cv::Point2f> GetCardMatchROI() = 0;

        virtual void EnableAlgoLog(bool enable) = 0;

        virtual EAuthMeEngineReturnCode Start() = 0;

        virtual AuthMeIDCardAntiFraudResult Run(const cv::Mat& srcImage) = 0;

        virtual EAuthMeEngineReturnCode Stop() = 0;

        virtual const std::string& GetJsonReport() = 0;

        virtual EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) = 0;
};

IIDCardAntiFraudService* CreateIDCardAntiFraudService();

}