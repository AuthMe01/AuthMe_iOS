#pragma once
#include "face_detection.hpp"
#include "nn_inference.hpp"
#include "face_detection_common.hpp"
#include "face_detection_capacity.hpp"

namespace AuthMe
{
class CFaceDetection : public IFaceDetection
{
    public:
        CFaceDetection();
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        void SetInferenceSize(const cv::Size& inferSize) override;
        std::vector<TFaceInfo> Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode CreateCapacityByModelVersion(std::unique_ptr<ICapacity_FaceDetection>& pCapacityProcess);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;

        float m_fScoreTh = 0.95f;
        std::unique_ptr<ICapacity_FaceDetection> m_pCapacityProcess = nullptr;

        cv::Mat m_blobImage;
};

}