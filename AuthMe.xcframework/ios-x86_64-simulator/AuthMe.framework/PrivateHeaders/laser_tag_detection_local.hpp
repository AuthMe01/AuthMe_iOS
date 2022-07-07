#pragma once
#include "laser_tag_detection.hpp"
#include "nn_inference.hpp"
#include "laser_tag_detection_capacity.hpp"

namespace AuthMe
{

class CLaserTagDetection : public ILaserTagDetection
{
    public:
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        ELaserTagStatus Detect(const cv::Mat& matImage, const std::vector<cv::Point>& vecVertice, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        float m_fScoreTh = 0.65f;
        std::unique_ptr <ICapacity_LaserTagDetection> m_pCapacityProcess = nullptr;

};

}