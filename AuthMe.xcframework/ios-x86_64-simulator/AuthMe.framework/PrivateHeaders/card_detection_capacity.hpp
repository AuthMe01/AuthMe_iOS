#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

const std::string strCardDetection_V0 = "0";
const std::string strCardDetection_V1 = "1";
const std::string strCardDetection_V2 = "2";

class ICapacity_CardDetection
{
    public:
        virtual ~ICapacity_CardDetection() {};
        virtual bool Initial(const std::map<std::string, std::vector<int64_t>>& inputShapes, const std::map<std::string, std::vector<int64_t>>& outputShapes) = 0;
        virtual std::vector<TTensorInfo> GetOutputBuffer() = 0;
        virtual std::vector<TTensorInfo> Preprocess(const cv::Mat &inputImage) = 0;
        virtual std::vector<cv::Point> Postprocess() = 0;
};

class Capacity_CardDetection_V0 : public ICapacity_CardDetection
{
    public:
        virtual ~Capacity_CardDetection_V0() = default;
        bool Initial(const std::map<std::string, std::vector<int64_t>>& inputShapes, const std::map<std::string, std::vector<int64_t>>& outputShapes) override;
        std::vector<TTensorInfo> GetOutputBuffer() override;
        std::vector<TTensorInfo> Preprocess(const cv::Mat &inputImage) override;
        std::vector<cv::Point> Postprocess() override;

    private:
        std::vector<cv::Point> GetPolygon(const cv::Mat& matNNOutput, const cv::Size orgSize);
        std::vector<cv::Point> GetMaxExtentShape(const std::vector<cv::Point>& vecPoints);
        void OrderClockwise4pts(std::vector<cv::Point>& vecVertices);

        cv::Size m_modelInputSize;
        cv::Size m_modelOutputSize;
        cv::Size m_inputImageSize;
        cv::Mat m_inputBuffer;
        cv::Mat m_outputBuffer;

        const double m_dHeatmapTh = 0.1;
};

using Capacity_CardDetection_V1 = Capacity_CardDetection_V0;

class Capacity_CardDetection_V2 : public ICapacity_CardDetection
{
    public:
        virtual ~Capacity_CardDetection_V2() = default;
        bool Initial(const std::map<std::string, std::vector<int64_t>>& inputShapes, const std::map<std::string, std::vector<int64_t>>& outputShapes) override;
        std::vector<TTensorInfo> GetOutputBuffer() override;
        std::vector<TTensorInfo> Preprocess(const cv::Mat &inputImage) override;
        std::vector<cv::Point> Postprocess() override;

    private:
        bool GetPoint(float* pBuffer, cv::Point2f& p);

        cv::Size m_modelInputSize;
        cv::Size m_modelOutputSize;
        cv::Size m_inputImageSize;
        cv::Mat m_inputBuffer;
        std::vector<float> m_outputBuffer;

        const double m_dHeatmapTh = 0.3;
        const float m_fMinAreaTh = 0.7f;
};

std::unique_ptr<ICapacity_CardDetection> CreateCapacity_CardDetection(std::string strTypeName);

}
