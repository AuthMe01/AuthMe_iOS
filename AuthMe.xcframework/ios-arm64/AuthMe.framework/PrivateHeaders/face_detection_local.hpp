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
        void SetInferenceSize(const cv::Size& inferSize) override;
        std::vector<TFaceInfo> Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        void InitModelParams(const cv::Size& inputSize);
        std::pair<cv::Mat, float> Preprocess(const cv::Mat &inputImage);
        std::vector<TFaceInfo> Postprocess(cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks, float fScale);
        std::vector<int> GetFacesIdx(const cv::Mat& matScores, float fScore);
        void SortIndexByScore(const cv::Mat& matScores, std::vector<int>& vecIndex);
        void NMS(const cv::Mat& matOutput, std::vector<int>& vecIndex, float fNMS_Th);
        std::vector<TFaceInfo> GenResult(const cv::Mat& matBoxes, const cv::Mat& matScores, const cv::Mat matLandmarks, const cv::Mat& matMasks, const std::vector<int>& vecIndex, float fScale);
        float GetScore(const cv::Mat& matOutput, const int iIdx);
        cv::Rect2f GetFaceRect(const cv::Mat& matOutput, int iIdx);
        std::vector<cv::Point2f> GetLandmark(const cv::Mat& matOutput, const int iIdx);
        std::vector<TAnchorBox> GenAnchor(const std::vector<std::pair<float, std::vector<float>>>& vecFeatureMap, const cv::Size2f& inputSize);
        void DecodeAndScaleBox(cv::Mat matBoxes, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift);
        void DecodeAndScaleLandmark(cv::Mat matOutput, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::vector<TAnchorBox> m_vecAnchor;

        cv::Size m_modelInputSize = cv::Size(192, 320);
        cv::Size m_outputBoxSize;
        cv::Size m_outputScoreSize;
        cv::Size m_outputLandmarkSize;
        cv::Size m_outputMasksSize;
        std::vector<std::pair<std::string, std::vector<int64_t>>> m_inputShape;
        std::vector<std::pair<std::string, std::vector<int64_t>>> m_outputShape;

        bool m_bDecode = true;
        float m_fScoreTh = 0.95f;
        float m_fNMSTh = 0.4f;
        size_t m_uiOutputTopK = 500;
        size_t m_uiNMSTopK = 50;

};

}