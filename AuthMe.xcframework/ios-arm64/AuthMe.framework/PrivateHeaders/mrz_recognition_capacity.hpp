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
const std::string strMRZRecognition_V1 = "1";
const std::string strMRZRecognition_V2 = "2";

class ICapacity_MRZRecognition
{
    public:
        virtual ~ICapacity_MRZRecognition() {};
        virtual bool Initial(IInferenceEngine* pEngine);
        virtual std::vector<TTensorInfo> Preprocess(const cv::Mat &inputImage, const std::vector<cv::Point2f>& vecVertices);
        virtual std::vector<TTensorInfo> GetOutputBuffer();
        virtual std::vector<std::string> Postprocess() = 0;

    protected:
        cv::Size m_modelInputSize;
        cv::Size m_modelOutputSize;
        std::vector<cv::Point2f> m_vecRefPoints;
        cv::Mat m_inputBuffer;
        std::vector<int64_t> m_outputBuffer;
};

class Capacity_MRZRecognition_V0: public ICapacity_MRZRecognition
{
    public:
        bool Initial(IInferenceEngine* pEngine) override;
        std::vector<std::string> Postprocess() override;

};

class Capacity_MRZRecognition_V2: public ICapacity_MRZRecognition
{
    public:
        bool Initial(IInferenceEngine* pEngine) override;
        std::vector<std::string> Postprocess() override;

    private:
        std::string Decoder(std::vector<int64_t> &outputBuffer, unsigned int staridx, unsigned int endidx);
        std::vector<int64_t> m_IndexBuffer;
        std::vector<char> m_DecodeTable;
};

std::unique_ptr<ICapacity_MRZRecognition> CreateCapacity_MRZRecognition(std::string strTypeName);

}
