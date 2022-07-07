#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strFaceAlignment_V0 = "0";

class ICapacity_FaceAlignment
{
    public:
        virtual ~ICapacity_FaceAlignment() {};
        virtual void Preprocess(const cv::Mat& inputImage, const cv::Rect2f& faceRect, cv::Mat& matModelInput, cv::Mat& transMatrix, const cv::Size& modelInputSize) = 0;
        virtual std::vector<cv::Point2f> PostProcess(const std::vector<float>& vecModelOutput, const cv::Mat& transMatrix, const cv::Size& modelInputSize) = 0;
};

class Capacity_FaceAlignment_V0 : public ICapacity_FaceAlignment
{
    public:
        void Preprocess(const cv::Mat& inputImage, const cv::Rect2f& faceRect, cv::Mat& matModelInput, cv::Mat& transMatrix, const cv::Size& modelInputSize);
        std::vector<cv::Point2f> PostProcess(const std::vector<float>& vecModelOutput, const cv::Mat& transMatrix, const cv::Size& modelInputSize);
};

std::unique_ptr<ICapacity_FaceAlignment> CreateCapacity_FaceAlignment(std::string strTypeName);

}
