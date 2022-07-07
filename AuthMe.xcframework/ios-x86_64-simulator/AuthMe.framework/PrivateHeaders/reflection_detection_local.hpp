#pragma once
#include "reflection_detection.hpp"
#include "nn_inference.hpp"
#include "reflection_detection_capacity.hpp"

namespace AuthMe
{

class CReflectionDetection: public IReflectionDetection
{
    public:
        virtual ~CReflectionDetection();
        EAuthMeEngineReturnCode Initial(const std::string & strModelPath, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        std::string GetModelInfo() const override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        cv::Mat Detect(const cv::Mat& inputImage, const std::vector<cv::Point>& vecVertices, cv::Mat* pResultImage = nullptr, AuthMeEngineDebugInfo* pInfo = nullptr) override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        cv::Mat Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point>& vecVertices);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;

        float m_fThreshold = 0.025f;
        std::unique_ptr <ICapacity_ReflectionDetection> m_pCapacityProcess = nullptr;
        cv::Mat m_modelOutput;
};

}