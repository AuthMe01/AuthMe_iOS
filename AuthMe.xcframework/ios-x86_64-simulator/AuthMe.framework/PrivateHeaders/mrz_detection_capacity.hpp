#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

const std::string strMRZDetection_V0 = "0";
const std::string strMRZDetection_V1 = "1";

class ICapacity_MRZDetection
{
    public:
        virtual ~ICapacity_MRZDetection() = default;
        virtual bool Initial(const IInferenceEngine* pEngine);
        virtual std::vector<TTensorInfo> Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point>& vertices);
        virtual std::vector<TTensorInfo> GetOutputBuffer() const;
        virtual std::vector<std::vector<cv::Point2f>> Postprocess() = 0;

    protected:
        cv::Size m_inputImageSize;
        cv::Size m_modelInputSize;
        cv::Size m_modelOutputSize;
        cv::Mat m_inputBuffer;
        cv::Mat m_outputBuffer;
        cv::Mat m_transMatrix;
        float m_fScaleDistance = 0.0f;
};

class Capacity_MRZDetection_V0: public ICapacity_MRZDetection
{
    public:
        std::vector<std::vector<cv::Point2f>> Postprocess() override;
};

std::unique_ptr<ICapacity_MRZDetection> CreateCapacity_MRZDetection(std::string strTypeName);

}
