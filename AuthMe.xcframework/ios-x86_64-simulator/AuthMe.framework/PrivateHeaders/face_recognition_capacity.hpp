#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const std::string strFaceRecognition_V0 = "0";

class ICapacity_FaceRecognition
{
    public:
        virtual ~ICapacity_FaceRecognition() {};
        virtual cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2f>& vecLandmark, const std::vector<cv::Point2f> vecRefPoints, const cv::Size& modelInputSize) = 0;
        virtual void Postprocess(std::vector<float>& vecTemplate) = 0;
};

class Capacity_FaceRecognition_V0: public ICapacity_FaceRecognition
{
    public:
        cv::Mat Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2f>& vecLandmark, const std::vector<cv::Point2f> vecRefPoints, const cv::Size& modelInputSize);
        void Postprocess(std::vector<float>& vecTemplate);
};

std::unique_ptr<ICapacity_FaceRecognition> CreateCapacity_FaceRecognition(std::string strTypeName);

}
