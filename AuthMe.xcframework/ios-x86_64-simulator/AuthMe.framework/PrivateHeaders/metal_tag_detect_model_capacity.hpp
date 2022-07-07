#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "metal_tag_detection.hpp"

namespace AuthMe
{

const std::string strMetalTagDetection_V0 = "0";
const std::string strMetalTagDetection_V1 = "1";

class ICapacity_MetalTagDetection
{
    public:
        virtual ~ICapacity_MetalTagDetection() {};
        virtual std::pair<cv::Mat, cv::Mat>Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, const std::vector<cv::Point2f>& vecRefPoints, const cv::Size & modelInputSize, const cv::Size targetSize) = 0;
        virtual std::vector<MetalTagReturnType> PostProcess(const cv::Mat& matMask, const cv::Mat& matLabel, const float m_fMaskTh, const int m_iPixelNumTh, const cv::Size modelOutputSize) = 0;
};

class Capacity_MetalTagDetection_V0 : public ICapacity_MetalTagDetection
{
    public:
        virtual ~Capacity_MetalTagDetection_V0() = default;
        std::pair<cv::Mat, cv::Mat>Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecVertices, const std::vector<cv::Point2f>& vecRefPoints, const cv::Size &modelInputSize, const cv::Size targetSize);
        std::vector<MetalTagReturnType> PostProcess(const cv::Mat& matMask, const cv::Mat& matLabel, const float m_fMaskTh, const int m_iPixelNumTh, const cv::Size modelOutputSize) ;
};

using Capacity_MetalTagDetection_V1 = Capacity_MetalTagDetection_V0;

std::unique_ptr<ICapacity_MetalTagDetection> CreateCapacity_MetalTagDetection(std::string strTypeName);

}

