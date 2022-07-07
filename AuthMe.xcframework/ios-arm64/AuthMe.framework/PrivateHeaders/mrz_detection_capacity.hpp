#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strMRZDetection_V0 = "0";

class ICapacity_MRZDetection
{
    public:
        virtual ~ICapacity_MRZDetection() {};
        virtual cv::Mat Preprocess(const cv::Mat& inputImage, const cv::Size& modelInputSize) = 0;
        virtual std::vector<cv::Point2f> Postprocess(const cv::Mat& matOutput, const cv::Size& targetSize, const cv::Size& modelOutputSize) = 0;
};

class Capacity_MRZDetection_V0: public ICapacity_MRZDetection
{
    public:
        cv::Mat Preprocess(const cv::Mat& inputImage, const cv::Size& modelInputSize);
        std::vector<cv::Point2f> Postprocess(const cv::Mat& matOutput, const cv::Size& targetSize, const cv::Size& modelOutputSize);
};

std::unique_ptr<ICapacity_MRZDetection> CreateCapacity_MRZDetection(std::string strTypeName);

}

