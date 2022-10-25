#pragma once
#include "engine_service_type.h"
#include "opencv2/core.hpp"
#include "engine_base.hpp"

namespace AuthMe
{

class IPassportService : public IEngineBase
{
    public:
        virtual ~IPassportService() = default;

        static std::string ToJson(const AuthMeMRZFieldTD3& field);

        static std::vector<AuthMeModelVersion> GetModelVersion();

        virtual const std::vector<AuthMeEngineDebugInfo> &GetDeBugInfo() = 0;

        virtual bool Initial(const AuthMePassportServiceModels& models) = 0;

        virtual void SetUIParams(const AuthMeServiceUIParams& params) = 0;

        virtual AuthMeServiceUIParams GetUIParams() const = 0;

        virtual void SetParams(const AuthMePassportServiceParams& params) = 0;

        virtual AuthMePassportServiceParams GetParams() const = 0;

        virtual void SetMatchROI(const std::vector<cv::Point2f>& vertices) = 0;

        virtual std::vector<cv::Point2f> GetMatchROI() const = 0;

        virtual void EnableAlgoLog(bool enable) = 0;

        virtual EAuthMeEngineReturnCode Start() = 0;

        virtual AuthMePassportServiceResult Run(const cv::Mat& srcImage) = 0;

        virtual EAuthMeEngineReturnCode Stop() = 0;

        virtual const std::string& GetJsonReport() = 0;

        virtual AuthMeMRZFieldTD3 GetFinalResult() const = 0;

        virtual EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) = 0;
};


IPassportService* CreatePassportService();

}
