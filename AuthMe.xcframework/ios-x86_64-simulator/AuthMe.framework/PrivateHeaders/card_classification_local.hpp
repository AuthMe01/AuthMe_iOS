#pragma once
#include "card_classification.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

class CCardClassification : public ICardClassification
{
    public:
        bool Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration) override;
        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration) override;
        void SetThreshold(const float fThreshold) override;
        float GetThreshold() const override;
        ECardClass Run(const cv::Mat& matInputImage, const std::vector<cv::Point2i>& vecPolygon, TEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon);
        ECardClass GetCardClass(const std::vector<float>& vecOutput);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        float m_fOutputTh = 0.65f;
};

}