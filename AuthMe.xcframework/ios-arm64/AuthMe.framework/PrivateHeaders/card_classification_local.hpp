#pragma once
#include "card_classification.hpp"
#include "nn_inference.hpp"
#include "card_classification_capacity.hpp"

namespace AuthMe
{

class CCardClassification : public ICardClassification
{
    public:
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration) override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration) override;
        void SetThreshold(const float fThreshold) override;
        float GetThreshold() const override;
        ECardClass Run(const cv::Mat& matInputImage, const std::vector<cv::Point2i>& vecPolygon, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon);
        ECardClass GetCardClass(const std::vector<float>& vecOutput);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::unique_ptr <ICapacity_CardClassification> m_pCapacityProcess = nullptr;
        float m_fOutputTh = 0.65f;
};

}