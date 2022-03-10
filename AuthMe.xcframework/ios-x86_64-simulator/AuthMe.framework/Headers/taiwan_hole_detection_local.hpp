#pragma once
#include "taiwan_hole_detection.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

class CTaiwanHoleDetection : public ITaiwanHoleDetection
{
    public:
        bool Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        ETaiwanHoleStatus Detect(const cv::Mat& matImage, const std::vector<cv::Point>& vecVertice, TEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        float m_fScoreTh = 0.8f;
};

}