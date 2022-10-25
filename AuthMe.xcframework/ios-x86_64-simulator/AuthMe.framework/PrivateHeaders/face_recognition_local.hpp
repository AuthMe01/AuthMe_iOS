#pragma once
#include "face_recognition.hpp"
#include "engine_utility.hpp"
#include "face_recognition_capacity.hpp"

namespace AuthMe
{

class CFaceRecognition : public IFaceRecognition
{
    public:
        virtual ~CFaceRecognition() = default;
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        std::string GetModelInfo() const override;
        size_t GetOutputLength() const override;
        std::vector<float> Encode(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecLandmark, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        double Compare(const std::vector<float>& vecTemplate1, const std::vector<float>& vecTemplate2) const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode CreateCapacity();

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::unique_ptr<ICapacity_FaceRecognition> m_pCapacityProcess = nullptr;
};

}