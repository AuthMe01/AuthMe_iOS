#pragma once
#include "fas_service_base.hpp"

namespace AuthMe
{

class CFASService_Active : public CFASService_Base
{
    public:
        virtual ~CFASService_Active() {};
        AuthMeFASResult Run(const cv::Mat& inputImage) override;
        void Start() override;

    private:
        void SwitchStageTo(EAuthMeFASServiceStage eStage);

        EAuthMeFASServiceStage m_eCurrentStage;
};

}
