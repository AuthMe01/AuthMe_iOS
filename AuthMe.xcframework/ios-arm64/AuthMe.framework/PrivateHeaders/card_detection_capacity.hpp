#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strCardDetection_V0 = "0";
const std::string strCardDetection_V1 = "1";

class ICapacity_CardDetection
{
    public:
        virtual ~ICapacity_CardDetection() {};
        virtual cv::Mat Preprocess(const cv::Mat &inputImage, const cv::Size &modelInputSize) = 0;
};

class Capacity_CardDetection_V0 : public ICapacity_CardDetection
{
    public:
        virtual ~Capacity_CardDetection_V0() = default;
        cv::Mat Preprocess(const cv::Mat &inputImage, const cv::Size &modelInputSize);
};

using Capacity_CardDetection_V1 = Capacity_CardDetection_V0;

std::unique_ptr<ICapacity_CardDetection> CreateCapacity_CardDetection(std::string strTypeName);

}
