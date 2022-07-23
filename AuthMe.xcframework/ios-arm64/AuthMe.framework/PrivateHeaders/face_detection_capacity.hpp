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

        virtual void GetDefaultParam(cv::Size &modelInputSize, bool &m_bDecode, float &m_fScoreTh, float &m_fNMSTh, size_t &m_uiOutputTopK, size_t &m_uiNMSTopK) = 0;

        virtual std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineInputShape(const cv::Size &modelInputSize) = 0;

        virtual std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineOutputShape(const int iAnchorNum) = 0;

        virtual void SetOutputSize(const int iAnchorNum, cv::Size &BoxSize, cv::Size &ScoreSize, cv::Size &LandmarkSize, cv::Size &markSize, cv::Size &ClsSize) = 0;

        virtual std::vector<TTensorInfo> SetEngineInput(cv::Mat &matModelInput) = 0;

        virtual std::vector<TTensorInfo> SetEngineOutput(cv::Mat &matBoxes, cv::Mat &matScores, cv::Mat &matLandmarks, cv::Mat &matMasks, cv::Mat &matCls) = 0;

        virtual std::vector<TFaceInfo>  Postprocess(cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks, cv::Mat &matCls,
                float fScale, cv::Size m_modelInputSize,
                float m_fScoreTh, float m_fNMSTh, size_t m_uiOutputTopK, size_t m_uiNMSTopK,
                bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor) = 0;

        virtual std::pair<cv::Mat, float> Preprocess(const cv::Mat & inputImage, cv::Size m_modelInputSize) = 0;

        virtual std::vector<TAnchorBox> GenAnchor(const cv::Size2f & inputSize) = 0;
};

class Capacity_FaceDetection_V0 : public ICapacity_FaceDetection
{
    public:
        void GetDefaultParam(cv::Size &modelInputSize, bool &m_bDecode, float &m_fScoreTh, float &m_fNMSTh, size_t &m_uiOutputTopK, size_t &m_uiNMSTopK);

        std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineInputShape(const cv::Size &modelInputSize);

        std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineOutputShape(const int iAnchorNum);

        void SetOutputSize(const int iAnchorNum, cv::Size &BoxSize, cv::Size &ScoreSize, cv::Size &LandmarkSize, cv::Size &markSize, cv::Size &ClsSize);

        std::vector<TTensorInfo> SetEngineInput(cv::Mat &matModelInput);
        
        std::vector<TTensorInfo> SetEngineOutput(cv::Mat &matBoxes, cv::Mat &matScores, cv::Mat &matLandmarks, cv::Mat &matMasks, cv::Mat &matCls);

        std::vector<TFaceInfo> Postprocess(cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks, cv::Mat &matCls,
                                           float fScale, cv::Size m_modelInputSize,
                                           float m_fScoreTh, float m_fNMSTh, size_t m_uiOutputTopK, size_t m_uiNMSTopK,
                                           bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor);

        std::pair<cv::Mat, float> Preprocess(const cv::Mat & inputImage, cv::Size m_modelInputSize);

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
        
        cv::Scalar m_paddingValue = cv::Scalar(104, 117, 123);

        void DecodeAndScaleBox(cv::Mat matBoxes, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift, bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor, const float variances[2]);

        void DecodeAndScaleLandmark(cv::Mat matLandmarks, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift, bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor, const float variances[2]);

        std::vector<TFaceInfo> GenResult(const cv::Mat& matBoxes,
                                        const cv::Mat& matScores,
                                        const cv::Mat matLandmarks,
                                        const cv::Mat& matMasks,
                                        const std::vector<int>& vecIndex,
                                        cv::Size m_modelInputSize,
                                        float fScale);

};

class Capacity_FaceDetection_V1 : public ICapacity_FaceDetection
{
    public:
        void GetDefaultParam(cv::Size &modelInputSize, bool &m_bDecode, float &m_fScoreTh, float &m_fNMSTh, size_t &m_uiOutputTopK, size_t &m_uiNMSTopK);

        std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineInputShape(const cv::Size &modelInputSize);

        std::vector<std::pair<std::string, std::vector<int64_t>>> GetEngineOutputShape(const int iAnchorNum);

        void SetOutputSize(const int iAnchorNum, cv::Size &BoxSize, cv::Size &ScoreSize, cv::Size &LandmarkSize, cv::Size &markSize, cv::Size &ClsSize);

        std::vector<TTensorInfo> SetEngineInput(cv::Mat &matModelInput);
        
        std::vector<TTensorInfo> SetEngineOutput(cv::Mat &matBoxes, cv::Mat &matScores, cv::Mat &matLandmarks, cv::Mat &matMasks, cv::Mat &matCls);

        std::vector<TFaceInfo> Postprocess(cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks, cv::Mat &matCls,
                                           float fScale, cv::Size m_modelInputSize,
                                           float m_fScoreTh, float m_fNMSTh, size_t m_uiOutputTopK, size_t m_uiNMSTopK,
                                           bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor);

        std::pair<cv::Mat, float> Preprocess(const cv::Mat & inputImage, cv::Size m_modelInputSize);

        std::vector<TAnchorBox> GenAnchor(const cv::Size2f & inputSize);

    private:
        cv::Size m_modelInputSize = cv::Size(320, 320);
        const std::vector<std::pair<float, std::vector<float>>> vecFeatureMap =
        {
            {8, {16, 32}},
            {16, {48, 96}},
            {32, {128, 256}},
        };

        cv::Scalar m_paddingValue = cv::Scalar(103, 117, 123);                

        void DecodeAndScaleBox(cv::Mat matBoxes, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift, std::vector<TAnchorBox> &m_vecAnchor);

        void DecodeAndScaleLandmark(cv::Mat matLandmarks, const std::vector<int> vecIndex, const cv::Size2f& scale, const cv::Point2f& shift, std::vector<TAnchorBox> &m_vecAnchor);
        
        std::vector<TFaceInfo> GenResult(const cv::Mat& matBoxes,
                                        const cv::Mat& matScores,
                                        const cv::Mat matLandmarks,
                                        const cv::Mat& matMasks,
                                        const cv::Mat& matCls,
                                        const std::vector<int>& vecIndex);

};

std::unique_ptr<ICapacity_FaceDetection> CreateCapacity_FaceDetection(std::string strTypeName);

}
