#pragma once
#include "nn_inference.hpp"
#include "face_anti_spoofing.hpp"
#include "face_anti_spoofing_capacity.hpp"

namespace AuthMe
{


class CFaceAntiSpoofingModel : public IFaceAntiSpoofing
{
    public:
        CFaceAntiSpoofingModel();
        virtual ~CFaceAntiSpoofingModel() = default;
        virtual EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        virtual EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        virtual EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        virtual void SetThreshold(float fThreshold) override;
        virtual float GetThreshold() const override;
        virtual void SetMinFrameNum(size_t uiLength) override;
        virtual size_t GetMinFrameNum() const override;
        virtual void Reset() override;
        virtual std::pair<EFaceAntiSpoofingStatus, float> Detect(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecLandmark, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        virtual std::string GetModelInfo() const override;
        virtual double TableMapping(double dValue) const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        void SetupModel();
        void Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecLandmark, const cv::Size& modelInputSize, cv::Mat& imgBGR, cv::Mat& bufferBGR, cv::Mat& bufferHSV);
        float Postprocess(const cv::Mat& matOutput);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::vector<double> m_vecTableSrc;
        std::vector<double> m_vecTableDst;
        cv::Size m_modelInputSize;
        cv::Size m_modelOutputSize;

        float m_fScoreTh = 0.8f;

        std::unique_ptr <ICapacity_FaceAntiSpoofing> m_pCapacityProcess = nullptr;
};

}
