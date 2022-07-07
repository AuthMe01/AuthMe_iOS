#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strFaceAntiSpoofing_V0 = "0";

class ICapacity_FaceAntiSpoofing
{
    public:
        virtual ~ICapacity_FaceAntiSpoofing() {};
        virtual void Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecLandmark, const cv::Size& modelInputSize, cv::Mat& imgBGR, cv::Mat& bufferBGR, cv::Mat& bufferHSV,
                                const std::vector<cv::Point2f>& vecRefPoint) = 0;
        virtual float Postprocess(const cv::Mat& matOutput) = 0;

};

class Capacity_FaceAntiSpoofing_V0 : public ICapacity_FaceAntiSpoofing
{
    public:
        void Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecLandmark, const cv::Size& modelInputSize, cv::Mat& imgBGR, cv::Mat& bufferBGR, cv::Mat& bufferHSV,
                        const std::vector<cv::Point2f>& vecRefPoint);
        float Postprocess(const cv::Mat& matOutput);

};

std::unique_ptr<ICapacity_FaceAntiSpoofing> CreateCapacity_FaceAntiSpoofing(std::string strTypeName);

}
