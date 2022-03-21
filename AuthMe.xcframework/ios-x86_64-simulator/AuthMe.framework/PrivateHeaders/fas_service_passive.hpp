#pragma once
#include "fas_service_base.hpp"

namespace AuthMe
{

class CFASService_Passive : public CFASService_Base
{
    public:
        virtual ~CFASService_Passive() {};
        AuthMeFASResult Run(const cv::Mat& inputImage) override;
};

}
