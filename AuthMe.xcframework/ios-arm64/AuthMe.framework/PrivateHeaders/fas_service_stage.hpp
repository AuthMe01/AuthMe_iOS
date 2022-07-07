#pragma once
#include "fas_service_local.hpp"
#include "opencv2/core.hpp"

namespace AuthMe
{

class IFASService_Stage
{
    public:
        virtual ~IFASService_Stage() {}

        virtual void SetParams(const AuthMeFASStageParams& params) = 0;

        virtual AuthMeFASStageParams GetParams() const = 0;

        virtual void Reset() = 0;

        // return status and score
        virtual std::pair<EAuthMeFASServiceStatus, float> Run(
            const cv::Mat& inputImage,
            AuthMeFASServiceInfo& info,
            const std::vector<cv::Point2f>& vecLandmark106,
            AuthMeEngineDebugInfo* pDebugInfo) = 0;
};

std::shared_ptr<IFASService_Stage> CreateStage_PassiveFAS(const CFASService* pService);
std::shared_ptr<IFASService_Stage> CreateStage_OpenMouth(const CFASService* pService);
std::shared_ptr<IFASService_Stage> CreateStage_CloseMouth(const CFASService* pService);
std::shared_ptr<IFASService_Stage> CreateStage_Smile(const CFASService* pService);

}
