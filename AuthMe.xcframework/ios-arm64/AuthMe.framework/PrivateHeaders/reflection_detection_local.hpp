#pragma once
#include "reflection_detection.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

class CReflectionDetection: public IReflectionDetection
{
    public:
        virtual ~CReflectionDetection();
        bool Initial(const std::string & strModelPath, const std::string strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        std::string GetModelInfo() const override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        cv::Mat Detect(const cv::Mat& inputImage, const std::vector<cv::Point>& vecVertices, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) override;

    private:
        void PostInitial();
        cv::Mat Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point>& vecVertices);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;

        float m_fThreshold = 0.025f;
};

}