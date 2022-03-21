#pragma once
#include "face_detection.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

typedef struct T_ANCHOR_BOX
{
    cv::Point2f center;
    cv::Size2f size;
} TAnchorBox;

class CFaceDetection : public IFaceDetection
{
    public:
        CFaceDetection();
        bool Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        std::vector<TFaceInfo> Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        cv::Mat Preprocess(const cv::Mat &inputImage);
        std::vector<TFaceInfo> Postprocess(cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks);
        std::vector<int> GetFacesIdx(const cv::Mat& matScores, float fScore);
        void SortIndexByScore(const cv::Mat& matScores, std::vector<int>& vecIndex);
        void NMS(const cv::Mat& matOutput, std::vector<int>& vecIndex, float fNMS_Th);
        std::vector<TFaceInfo> GenResult(const cv::Mat& matBoxes, const cv::Mat& matScores, const cv::Mat matLandmarks, const cv::Mat& matMasks, const std::vector<int>& vecIndex);
        float GetScore(const cv::Mat& matOutput, const int iIdx);
        cv::Rect2f GetFaceRect(const cv::Mat& matOutput, int iIdx);
        std::vector<cv::Point2f> GetLandmark(const cv::Mat& matOutput, const int iIdx);
        std::vector<TAnchorBox> GenAnchor(const std::vector<std::pair<float, std::vector<float>>>& vecFeatureMap, const cv::Size2f& inputSize);
        void DecodeAndScaleBox(cv::Mat matBoxes, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift);
        void DecodeAndScaleLandmark(cv::Mat matOutput, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        float m_fScale = 0.0f;
        std::vector<TAnchorBox> m_vecAnchor;

        bool m_bDecode = true;
        float m_fScoreTh = 0.95f;
        float m_fNMSTh = 0.4f;
        size_t m_uiOutputTopK = 500;
        size_t m_uiNMSTopK = 50;

};

}