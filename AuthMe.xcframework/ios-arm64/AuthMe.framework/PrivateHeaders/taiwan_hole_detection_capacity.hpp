#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strTaiwanHoleDetection_V0 = "0";

class ICapacity_TaiwanHoleDetection
{
    public:
        virtual ~ICapacity_TaiwanHoleDetection() {};
        virtual cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, cv::Size2i modelInputSize) = 0;
        virtual void PostProcess() = 0;
};

class Capacity_TaiwanHoleDetection_V0 : public ICapacity_TaiwanHoleDetection
{
    public:
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2i>& vecPolygon, cv::Size2i modelInputSize);
        void PostProcess();
};

std::unique_ptr<ICapacity_TaiwanHoleDetection> CreateCapacity_TaiwanHoleDetection(std::string strTypeName);

}

