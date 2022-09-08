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
class ICapacity_FaceDetection
{
    public:
        virtual ~ICapacity_FaceDetection() {};

        virtual void GetDefaultParam(cv::Size &modelInputSize, float &m_fScoreTh, float &m_fNMSTh, size_t &m_uiOutputTopK, size_t &m_uiNMSTopK, bool &m_bDecode) = 0;

        virtual void SetOutputSize(bool m_bDecode, cv::Size2i inputSize) = 0;

        virtual std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineInputShape() = 0;

        virtual std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineOutputShape() = 0;

        virtual std::vector<TTensorInfo> SetEngineInput(cv::Mat &matModelInput) = 0;

        virtual std::vector<TTensorInfo> SetEngineOutput() = 0;

        virtual std::pair<cv::Mat, float> Preprocess(const cv::Mat & inputImage) = 0;

        virtual std::vector<TFaceInfo> Postprocess(float fScale, float m_fScoreTh, float m_fNMSTh, size_t m_uiOutputTopK, size_t m_uiNMSTopK, bool m_bDecode) = 0;
};

class Capacity_FaceDetection_V0 : public ICapacity_FaceDetection
{
    public:
        void GetDefaultParam(cv::Size &modelInputSize, float &m_fScoreTh, float &m_fNMSTh, size_t &m_uiOutputTopK, size_t &m_uiNMSTopK, bool &m_bDecode);

        void SetOutputSize(bool m_bDecode, cv::Size2i inputSize);

        std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineInputShape();

        std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineOutputShape();

        std::vector<TTensorInfo> SetEngineInput(cv::Mat &matModelInput);

        std::vector<TTensorInfo> SetEngineOutput();

        std::pair<cv::Mat, float> Preprocess(const cv::Mat & inputImage);

        std::vector<TFaceInfo> Postprocess(float fScale, float m_fScoreTh, float m_fNMSTh, size_t m_uiOutputTopK, size_t m_uiNMSTopK, bool m_bDecode);

    private:
        void DecodeAndScaleBox(cv::Mat matBoxes, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift, bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor, const float variances[2]);

        void DecodeAndScaleLandmark(cv::Mat matLandmarks, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift, bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor, const float variances[2]);

        std::vector<TFaceInfo> GenResult(const std::vector<int>& vecIndex,
                                         cv::Size m_modelInputSize,
                                         float fScale);

        std::vector<TAnchorBox> GenAnchor(const cv::Size2f & inputSize);

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

        cv::Size m_outputBoxSize;
        cv::Size m_outputScoreSize;
        cv::Size m_outputLandmarkSize;
        cv::Size m_outputMasksSize;

        cv::Mat m_matBoxes;
        cv::Mat m_matScores;
        cv::Mat m_matLandmarks;
        cv::Mat m_matMasks;

        std::vector<TAnchorBox> m_vecAnchor;
};

class Capacity_FaceDetection_V1 : public ICapacity_FaceDetection
{
    public:
        void GetDefaultParam(cv::Size &modelInputSize, float &m_fScoreTh, float &m_fNMSTh, size_t &m_uiOutputTopK, size_t &m_uiNMSTopK, bool &m_bDecode);

        void SetOutputSize(bool m_bDecode, cv::Size2i inputSize);

        std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineInputShape();

        std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineOutputShape();

        std::vector<TTensorInfo> SetEngineInput(cv::Mat &matModelInput);

        std::vector<TTensorInfo> SetEngineOutput();

        std::pair<cv::Mat, float> Preprocess(const cv::Mat &inputImage);

        std::vector<TFaceInfo> Postprocess(float fScale, float m_fScoreTh, float m_fNMSTh, size_t m_uiOutputTopK, size_t m_uiNMSTopK, bool m_bDecode);

    private:
        void DecodeAndScaleBox(cv::Mat matBoxes, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift, std::vector<TAnchorBox> &m_vecAnchor);

        void DecodeAndScaleLandmark(cv::Mat matLandmarks, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift, std::vector<TAnchorBox> &m_vecAnchor);

        std::vector<TFaceInfo> GenResult(const std::vector<int>& vecIndex);

        std::vector<TAnchorBox> GenAnchor(const cv::Size2f & inputSize);

        const std::vector<std::pair<float, std::vector<float>>> vecFeatureMap =
        {
            {8, {16, 32}},
            {16, {48, 96}},
            {32, {128, 256}},
        };

        cv::Size m_modelInputSize = cv::Size(320, 320);

        cv::Scalar m_paddingValue = cv::Scalar(103, 117, 123);

        cv::Size m_outputBoxSize;
        cv::Size m_outputScoreSize;
        cv::Size m_outputLandmarkSize;
        cv::Size m_outputPoseSize;
        cv::Size m_outputClsSize;

        cv::Mat m_matBoxes;
        cv::Mat m_matScores;
        cv::Mat m_matLandmarks;
        cv::Mat m_matPose;
        cv::Mat m_matCls;

        std::vector<TAnchorBox> m_vecAnchor;
};

std::unique_ptr<ICapacity_FaceDetection> CreateCapacity_FaceDetection(std::string strTypeName);

}
