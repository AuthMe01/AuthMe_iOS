#pragma once
#include "card_detection.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

class CCardDetection : public ICardDetection
{
    public:
        bool Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration) override;
        std::vector<cv::Point> Detect(const cv::Mat& matInputImage, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        cv::Mat Preprocess(const cv::Mat &inputImage);
        std::vector<cv::Point> GetPolygon(const cv::Mat& matNNOutput, const cv::Size orgSize);
        cv::Rect GetRoi(const cv::Mat& matStats, int iLabel);
        cv::Point2f CalcWeightedCenter(const cv::Mat& matLabels, const cv::Mat& matNNOutput, const int iLabel, const cv::Rect& roi);
        std::vector<cv::Point> GetMaxExtentShape(const std::vector<cv::Point>& vecPoints);
        void OrderClockwise(std::vector<cv::Point>& vecVertices);
        void DrawHeatMap(const cv::Mat& matImage, const cv::Mat& matNNOutput, cv::Mat& result, double dHeatmapRatio = 0.4);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
};

}