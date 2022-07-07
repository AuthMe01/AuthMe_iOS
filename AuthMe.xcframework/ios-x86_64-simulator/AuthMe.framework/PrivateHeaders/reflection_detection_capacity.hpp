#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strReflectionDetection_V0 = "0";
const std::string strReflectionDetection_V1 = "1";

class ICapacity_ReflectionDetection
{
    public:
        virtual ~ICapacity_ReflectionDetection() {};
        virtual cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, const std::vector<cv::Point2f>& vecRefPoints, const cv::Size &modelInputSize) = 0;

};

class Capacity_ReflectionDetection_V0 : public ICapacity_ReflectionDetection
{
    public:
        virtual ~Capacity_ReflectionDetection_V0() = default;
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, const std::vector<cv::Point2f>& vecRefPoints, const cv::Size &modelInputSize);

};

using Capacity_ReflectionDetection_V1 = Capacity_ReflectionDetection_V0;

std::unique_ptr<ICapacity_ReflectionDetection> CreateCapacity_ReflectionDetection(std::string strTypeName);

}

