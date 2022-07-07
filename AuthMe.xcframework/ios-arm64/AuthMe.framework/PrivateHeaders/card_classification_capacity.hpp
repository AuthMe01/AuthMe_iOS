#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strCardClassification_V0 = "0";
const std::string strCardClassification_V1 = "1";

class ICapacity_CardClassification
{
    public:
        virtual ~ICapacity_CardClassification() {};
        virtual cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, const std::vector<cv::Point2f>& vecRefPoints, const cv::Size &modelInputSize) = 0;
};

class Capacity_CardClassification_V0 : public ICapacity_CardClassification
{
    public:
        virtual ~Capacity_CardClassification_V0() = default;
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, const std::vector<cv::Point2f>& vecRefPoints, const cv::Size &modelInputSize);
};

using Capacity_CardClassification_V1 = Capacity_CardClassification_V0;

std::unique_ptr<ICapacity_CardClassification> CreateCapacity_CardClassification(std::string strTypeName);

}
