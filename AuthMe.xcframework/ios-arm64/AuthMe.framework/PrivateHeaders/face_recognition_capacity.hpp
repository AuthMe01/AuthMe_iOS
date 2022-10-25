#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

const std::string strFaceRecognition_V0 = "0";

class ICapacity_FaceRecognition
{
    public:
        virtual ~ICapacity_FaceRecognition() = default;
        virtual size_t GetOutputLength() const = 0;
        virtual std::vector<TTensorInfo> Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2f>& vecLandmark) = 0;
        virtual std::vector<TTensorInfo> GetOutputBuffer() = 0;
        virtual std::vector<float> Postprocess() = 0;
};

class Capacity_FaceRecognition_V0: public ICapacity_FaceRecognition
{
    public:
        Capacity_FaceRecognition_V0();
        size_t GetOutputLength() const override;
        std::vector<TTensorInfo> GetOutputBuffer() override;
        std::vector<TTensorInfo> Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2f>& vecLandmark) override;
        std::vector<float> Postprocess() override;

    private:
        const cv::Size m_modelInputSize = {112, 112};
        const cv::Size m_modelOutputSize = {1, 1024};

        const std::vector<cv::Point2f> m_vecRefPoints =
        {
            {38.29459953f, 51.69630051f},
            {73.53179932f, 51.50139999f},
            {56.02519989f, 71.73660278f},
            {41.54930115f, 92.36550140f},
            {70.72990036f, 92.20410156f},
        };

        cv::Mat m_inputBuffer;
        std::vector<float> m_outputBuffer;

};

std::unique_ptr<ICapacity_FaceRecognition> CreateCapacity_FaceRecognition(std::string strTypeName);

}
