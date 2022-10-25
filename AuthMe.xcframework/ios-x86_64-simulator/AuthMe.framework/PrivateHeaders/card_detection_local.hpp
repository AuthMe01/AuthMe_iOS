#pragma once
#include "card_detection.hpp"
#include "nn_inference.hpp"
#include "card_detection_capacity.hpp"

namespace AuthMe
{

class CCardDetection : public ICardDetection
{
    public:
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration) override;
        std::vector<cv::Point> Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::unique_ptr <ICapacity_CardDetection> m_pCapacityProcess = nullptr;
};

}