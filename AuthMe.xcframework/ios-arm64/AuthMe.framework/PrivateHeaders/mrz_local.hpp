#pragma once
#include "mrz_service.hpp"
#include "mrz_detection.hpp"
#include "mrz_recognition.hpp"

namespace AuthMe
{

class CMRZ : public IMRZService
{
    public:
        CMRZ();
        virtual ~CMRZ();
        const std::vector<AuthMeEngineDebugInfo>& GetDeBugInfo() override;
        bool Initial(const AuthMeMRZModels& models) override;
        void SetUIParams(const AuthMeV3ServiceUIParams& params) override;
        AuthMeV3ServiceUIParams GetUIParams() const override;
        void SetParams(const AuthMeMRZParams& params) override;
        AuthMeMRZParams GetParams() const override;
        AuthMeMRZResult Run(const cv::Mat& srcImage) override;

    private:
        IMRZDetection* m_pMRZDetect = nullptr;
        IMRZRecognition* m_pMRZRecog = nullptr;

        AuthMeV3ServiceUIParams m_uiParams;
        AuthMeMRZParams m_params;

        std::vector<AuthMeEngineDebugInfo> m_vecDebugInfo;

};

}
