#pragma once
#include <string>
#include <vector>
#include "engine_service_type.h"
#include "opencv2/core.hpp"
#include "engine_base.hpp"

namespace AuthMe
{

class IFASService : public IEngineBase
{
    public:
        virtual ~IFASService() {}

        static std::vector<AuthMeModelVersion> GetModelVersion();

        virtual std::vector<AuthMeEngineDebugInfo> &GetDeBugInfo() = 0;

        virtual bool Initial(const AuthMeFASServiceModels& models) = 0;

        virtual void SetUIParams(const AuthMeServiceUIParams& params) = 0;

        virtual AuthMeServiceUIParams GetUIParams() const = 0;

        virtual void SetParams(const AuthMeFASParams& params) = 0;

        virtual AuthMeFASParams GetParams() const = 0;

        // return a rect in normalized axis, i.e., l,t,w,h in range [0~1], representing previewPosition
        virtual cv::Rect2f GetNormalizedFaceROI() const = 0;

        virtual void SetStage(const std::vector<EAuthMeFASServiceStage>& vecStage) = 0;

        virtual std::vector<EAuthMeFASServiceStage> GetStage() const = 0;

        virtual void SetStageParams(const AuthMeFASStageParams& params, int iIndex) = 0;

        virtual AuthMeFASStageParams GetStageParams(int iIndex) const = 0;

        virtual void EnableAlgoLog(bool enable) = 0;

        virtual EAuthMeEngineReturnCode Start() = 0;

        virtual AuthMeFASResult Run(const cv::Mat& inputImage) = 0;

        virtual EAuthMeEngineReturnCode Stop() = 0;

        virtual const std::string& GetJsonReport() = 0;

        virtual EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) = 0;
};

IFASService* CreateFASService();

}
