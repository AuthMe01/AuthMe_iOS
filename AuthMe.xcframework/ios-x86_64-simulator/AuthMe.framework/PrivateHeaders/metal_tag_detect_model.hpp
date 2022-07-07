#pragma once
#include "metal_tag_detection.hpp"
#include "nn_inference.hpp"
#include "metal_tag_detect_model_capacity.hpp"

namespace AuthMe
{

class CMetalTagDetection : public IMetalTagDetection
{
    public:
        ~CMetalTagDetection();
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        std::vector<MetalTagReturnType> Detect(const cv::Mat& inputImage,
                                               const std::vector<cv::Point>& vecVertices,
                                               cv::Mat* pResultImage = nullptr,
                                               AuthMeEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        void DrawDegugImage(cv::Mat& image, const std::vector<MetalTagReturnType>& vecResult);
        std::pair<cv::Mat, cv::Mat> Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point>& vecVertices);
        std::vector<MetalTagReturnType> PostProcess(const cv::Mat& matMask, const cv::Mat& matLabel);
        std::vector<int> SortIdxByArea(const cv::Mat& stats);
        void RemoveSmallArea(std::vector<int>& vecIdx, const cv::Mat& stats, int iThreshold);
        EIDCardMetalTagStatus GetMetalTagType(const cv::Mat& matLabel, const cv::Rect& roi);
        std::vector<cv::Point> GetPosition(const cv::Mat& stats, int iLabel);
        std::vector<MetalTagReturnType> ReorderResult(const std::vector<MetalTagReturnType>& vecResultOrg);
        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::vector<cv::Point2f> m_vecRefPoints;
        float m_fDetectTh = 0.0f;
        float m_fMaskTh = 0.6f;
        int m_iPixelNumTh = 20;
        cv::Mat m_matMask;
        cv::Mat m_matLabel;
        std::unique_ptr <ICapacity_MetalTagDetection> m_pCapacityProcess = nullptr;


};

}