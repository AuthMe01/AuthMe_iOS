#pragma once
#include "face_anti_spoofing.hpp"
#include "nn_inference.hpp"
#include "utility_moving_window.hpp"

#define MOVING_AVG_DEFAULT_WINDOW_LENGTH 3

namespace AuthMe
{

class CFaceAntiSpoofing : public IFaceAntiSpoofing
{
    public:
        CFaceAntiSpoofing();
        bool Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        void SetMinFrameNum(size_t uiLength) override;
        size_t GetMinFrameNum() const override;
        void Reset() override;
        EFaceAntiSpoofingStatus Detect(const cv::Mat& matImage, const std::vector<cv::Point2f>& vecLandmark, float& fScore, TEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        void InitialSetup();
        void GetParamsFromModel();
        void SetupModel();
        void SetupRuntimeParams();
        void Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecLandmark, const cv::Size& modelInputSize, cv::Mat& imgBGR, cv::Mat& bufferBGR, cv::Mat& bufferHSV);
        float Postprocess(const cv::Mat& matOutput);
        double TableMapping(double fScore);
        bool HasImageDiff(const cv::Mat& preGray, const cv::Mat& currGray);


        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        CMovingWindow<double> m_ScoreWindow;
        CMovingWindow<double> m_DiffMeanWindow;
        std::vector<double> m_vecTableSrc;
        std::vector<double> m_vecTableDst;
        cv::Size m_modelInputSize;
        cv::Size m_modelOutputSize;
        cv::Mat m_eyeMask;
        cv::Mat m_prevWarppedGray;
        int m_iEyeMaskArea = 0;

        float m_fScoreTh = 0.8f;
        const double m_dBBandScale = 1.6;
        const size_t m_uiBBandMaxLength = 5;
        const size_t m_uiBBandMinLengthNeeded = 3;
};

}