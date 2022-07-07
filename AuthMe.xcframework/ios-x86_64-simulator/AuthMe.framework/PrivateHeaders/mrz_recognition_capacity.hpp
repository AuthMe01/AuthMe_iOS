#pragma once
#include <string>
#include <memory>
#include <algorithm>
#include "engine_utility.hpp"
#include "utility_define.hpp"
#include "opencv2/core.hpp"


namespace AuthMe
{

const std::string strMRZRecognition_V0 = "0";

class ICapacity_MRZRecognition
{
    public:
        virtual ~ICapacity_MRZRecognition() {};
        virtual cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2f>& vecVertices, const std::vector<cv::Point2f> vecRefPoints, const cv::Size& modelInputSize) = 0;
        virtual bool Postprocess(const std::vector<int64_t>& vecOutput, TMRZFieldTD3& tField) = 0;
};

class Capacity_MRZRecognition_V0: public ICapacity_MRZRecognition
{
    public:
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2f>& vecVertices, const std::vector<cv::Point2f> vecRefPoints, const cv::Size& modelInputSize);
        bool Postprocess(const std::vector<int64_t>& vecOutput, TMRZFieldTD3& tField);
};

std::unique_ptr<ICapacity_MRZRecognition> CreateCapacity_MRZRecognition(std::string strTypeName);

}
