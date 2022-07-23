#pragma once
#include "engine_service_type.h"
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "card_detection.hpp"
#include "card_classification.hpp"
#include "reflection_detection.hpp"

namespace AuthMe
{

class IMRZService : public IEngineBase
{
    public:
        virtual ~IMRZService() {}

        static std::vector<AuthMeModelVersion> GetModelVersion();

        virtual const std::vector<AuthMeEngineDebugInfo> &GetDeBugInfo() = 0;

        virtual bool Initial(const AuthMeMRZModels& models) = 0;

        virtual void SetUIParams(const AuthMeV3ServiceUIParams& params) = 0;

        virtual AuthMeV3ServiceUIParams GetUIParams() const = 0;

        virtual void SetParams(const AuthMeMRZParams& params) = 0;

        virtual AuthMeMRZParams GetParams() const = 0;

        virtual AuthMeMRZResult Run(const cv::Mat& srcImage) = 0;

        virtual EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) = 0;
};


IMRZService* CreateMRZService();

}
