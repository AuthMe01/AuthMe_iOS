#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "nn_inference.hpp"
#include "face_detection_common.hpp"

namespace AuthMe
{

const std::string strFaceDetection_V0 = "0";

class ICapacity_FaceDetection
{
    public:
        virtual ~ICapacity_FaceDetection() {};
        virtual std::vector<TFaceInfo>  Postprocess(cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks,
                float fScale, cv::Size m_modelInputSize,
                float m_fScoreTh, float m_fNMSTh, size_t m_uiOutputTopK, size_t m_uiNMSTopK,
                bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor, const float variances[2]) = 0;

        virtual std::pair<cv::Mat, float> Preprocess(const cv::Mat & inputImage, cv::Size m_modelInputSize) = 0;


};

class Capacity_FaceDetection_V0 : public ICapacity_FaceDetection
{
    public:
        std::vector<TFaceInfo> Postprocess(cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks,
                                           float fScale, cv::Size m_modelInputSize,
                                           float m_fScoreTh, float m_fNMSTh, size_t m_uiOutputTopK, size_t m_uiNMSTopK,
                                           bool m_bDecode, std::vector<TAnchorBox> &m_vecAnchor, const float variances[2]);

        std::pair<cv::Mat, float> Preprocess(const cv::Mat & inputImage, cv::Size m_modelInputSize);

};

std::unique_ptr<ICapacity_FaceDetection> CreateCapacity_FaceDetection(std::string strTypeName);

}
