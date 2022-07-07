#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strLaserTagDetection_V0 = "0";

class ICapacity_LaserTagDetection
{
    public:
        virtual ~ICapacity_LaserTagDetection() {};
        virtual cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, const std::vector<cv::Point2f>& vecRefPoints, const cv::Size &modelInputSize) = 0;
};

class Capacity_LaserTagDetection_V0 : public ICapacity_LaserTagDetection
{
    public:
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, const std::vector<cv::Point2f>& vecRefPoints, const cv::Size &modelInputSize);
};

std::unique_ptr<ICapacity_LaserTagDetection> CreateCapacity_LaserTagDetection(std::string strTypeName);

}

