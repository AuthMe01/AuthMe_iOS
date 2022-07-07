#pragma once
#include "taiwan_hole_detection.hpp"
#include "nn_inference.hpp"
#include "taiwan_hole_detection_capacity.hpp"

namespace AuthMe
{

class CTaiwanHoleDetection : public ITaiwanHoleDetection
{
    public:
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        ETaiwanHoleStatus Detect(const cv::Mat& matImage, const std::vector<cv::Point>& vecVertice, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        float m_fScoreTh = 0.8f;
        std::unique_ptr <ICapacity_TaiwanHoleDetection> m_pCapacityProcess = nullptr;
};

}