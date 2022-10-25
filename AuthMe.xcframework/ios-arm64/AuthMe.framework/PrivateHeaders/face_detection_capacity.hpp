#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "nn_inference.hpp"
#include "face_detection_common.hpp"

namespace AuthMe
{

const std::string strFaceDetection_V0 = "0";
const std::string strFaceDetection_V1 = "1";
const std::string strFaceDetection_V2 = "2";

class ICapacity_FaceDetection
{
    public:
        virtual ~ICapacity_FaceDetection() {};

        virtual void GetDefaultParam(float &fScoreTh) = 0;

        virtual void SetupEngine(IInferenceEngine* pEngine, cv::Size inputSize = {}) = 0;

        virtual std::vector<TTensorInfo> GetOutputBuffer() = 0;

        virtual std::vector<TTensorInfo> Preprocess(const cv::Mat & inputImage) = 0;

        virtual std::vector<TFaceInfo> Postprocess(float fScoreTh) = 0;
};

class Capacity_FaceDetection_V0 : public ICapacity_FaceDetection
{
    public:
        void GetDefaultParam(float &fScoreTh) override;

        void SetupEngine(IInferenceEngine* pEngine, cv::Size inputSize = {}) override;

        std::vector<TTensorInfo> GetOutputBuffer() override;

        std::vector<TTensorInfo> Preprocess(const cv::Mat& inputImage) override;

        std::vector<TFaceInfo> Postprocess(float fScoreTh) override;

    private:
        void SetInputSize(cv::Size inputSize);
        std::vector<std::pair<std::string, std::vector<int64_t>>> GetInputShape() const;
        std::vector<std::pair<std::string, std::vector<int64_t>>> GetOutputShape() const;
        void DecodeAndScaleBox(cv::Mat& matBoxes, const std::vector<int>& vecIndex, const cv::Size2f& scale, const cv::Point2f& shift);
        void DecodeAndScaleLandmark(cv::Mat& matLandmarks, const std::vector<int>& vecIndex, const cv::Size2f& scale, const cv::Point2f& shift);
        std::vector<TFaceInfo> GenResult(const std::vector<int>& vecIndex, cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks);
        std::vector<TAnchorBox> GenAnchor(const cv::Size2f & inputSize);

    private:
        const std::vector<std::pair<float, std::vector<float>>> vecFeatureMap =
        {
            {8, {10, 16, 24}},
            {16, {32, 48}},
            {32, {64, 96}},
            {64, {128, 192, 256}}
        };

        const float variances[2] = {0.1f, 0.2f};

        cv::Size m_modelInputSize = cv::Size(192, 320);

        cv::Scalar m_paddingValue = cv::Scalar(104, 117, 123);

        bool m_bDecode = true;
        float m_fNMSTh = 0.4f;
        float m_fImageScale = 0.0f;
        size_t m_uiOutputTopK = 500;
        size_t m_uiNMSTopK = 50;

        cv::Mat m_matInputBuffer;

        cv::Mat m_matBoxes;
        cv::Mat m_matScores;
        cv::Mat m_matLandmarks;
        cv::Mat m_matMasks;

        std::vector<TAnchorBox> m_vecAnchor;
};

class Capacity_FaceDetection_V1 : public ICapacity_FaceDetection
{
    public:
        void GetDefaultParam(float &fScoreTh) override;

        void SetupEngine(IInferenceEngine* pEngine, cv::Size inputSize = {}) override;

        std::vector<TTensorInfo> GetOutputBuffer() override;

        std::vector<TTensorInfo> Preprocess(const cv::Mat &inputImage) override;

        std::vector<TFaceInfo> Postprocess(float fScoreTh) override;

    private:
        void SetInputSize(cv::Size inputSize);
        std::vector<std::pair<std::string, std::vector<int64_t>>> GetInputShape() const;
        std::vector<std::pair<std::string, std::vector<int64_t>>> GetOutputShape() const;
        void DecodeAndScaleLandmark(cv::Mat& matLandmarks, const std::vector<int>& vecIndex, const cv::Size2f& scale);
        std::vector<TFaceInfo> GenResult(const std::vector<int>& vecIndex, cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matPose, cv::Mat& matCls);
        std::vector<TAnchorBox> GenAnchor(const cv::Size2f& inputSize);

    private:
        const std::vector<std::pair<float, std::vector<float>>> vecFeatureMap =
        {
            {8, {16, 32}},
            {16, {48, 96}},
            {32, {128, 256}},
        };

        cv::Size m_modelInputSize = cv::Size(320, 320);

        cv::Scalar m_paddingValue = cv::Scalar(103, 117, 123);

        bool m_bDecode = true;
        float m_fNMSTh = 0.4f;
        float m_fImageScale = 0.0f;
        size_t m_uiOutputTopK = 500;
        size_t m_uiNMSTopK = 50;

        cv::Mat m_matInputBuffer;

        cv::Mat m_matBoxes;
        cv::Mat m_matScores;
        cv::Mat m_matLandmarks;
        cv::Mat m_matPose;
        cv::Mat m_matCls;

        std::vector<TAnchorBox> m_vecAnchor;
};

class Capacity_FaceDetection_V2 : public ICapacity_FaceDetection
{
    public:
        Capacity_FaceDetection_V2(const IInferenceEngine* pEngine);

        void GetDefaultParam(float &fScoreTh) override;

        void SetupEngine(IInferenceEngine* pEngine, cv::Size inputSize = {}) override;

        std::vector<TTensorInfo> GetOutputBuffer() override;

        std::vector<TTensorInfo> Preprocess(const cv::Mat &inputImage) override;

        std::vector<TFaceInfo> Postprocess(float fScoreTh) override;

    private:
        void SetInputSize(cv::Size inputSize);
        std::vector<std::pair<std::string, std::vector<int64_t>>> GetInputShape() const;
        std::vector<std::pair<std::string, std::vector<int64_t>>> GetOutputShape() const;
        void GenPriorCenterAndBuffer(const cv::Size& inputSize);
        void DecodeBox(cv::Mat& matBoxes, const std::vector<int>& vecIndex);
        void DecodeLandmark(cv::Mat& matLandmarks, const std::vector<int>& vecIndex);
        std::vector<TFaceInfo> GenResult(const std::vector<int>& vecIndex,
                                         cv::Mat& matBoxes,
                                         cv::Mat& matScores,
                                         cv::Mat& matLandmarks,
                                         cv::Mat& matPose,
                                         cv::Mat& matCls);

    private:
        float m_fNMSTh = 0.0f;
        float m_fDefaultScoreTh = 0.0f;
        float m_fImageScale = 0.0f;
        cv::Size m_modelInputSize = {640, 640};
        cv::Scalar m_paddingValue;
        std::vector<float> m_ancScales;
        std::vector<std::vector<int>> m_ancStrides;

        std::vector<cv::Point2f> m_priorCenters;
        cv::Mat m_matInputBuffer;
        std::vector<TTensorInfo> m_outputTensorInfo;
        std::vector<std::pair<std::string, std::vector<int64_t>>> m_outputShape;

        cv::Mat m_matBoxes;
        cv::Mat m_matScores;
        cv::Mat m_matLandmarks;
        cv::Mat m_matPose;
        cv::Mat m_matCls;
};

std::unique_ptr<ICapacity_FaceDetection> CreateCapacity_FaceDetection(std::string strTypeName, IInferenceEngine* pEngine);

}
