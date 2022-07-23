#pragma once
#include "face_detection.hpp"
#include "nn_inference.hpp"
#include "face_detection_common.hpp"
#include "face_detection_capacity.hpp"

namespace AuthMe
{
class CFaceDetection : public IFaceDetection
{
    public:
        CFaceDetection();
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        void SetThreshold(float fThreshold) override;
        float GetThreshold() const override;
        void SetInferenceSize(const cv::Size& inferSize) override;
        std::vector<TFaceInfo> Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        void SetParamByModelInputSize(const cv::Size& inputSize);

        void InitModelParams(const cv::Size& inputSize);
  
        std::pair<cv::Mat, float> Preprocess(const cv::Mat &inputImage);
        std::vector<TFaceInfo> Postprocess(cv::Mat& matBoxes, cv::Mat& matScores, cv::Mat& matLandmarks, cv::Mat& matMasks, cv::Mat &matCls, float fScale);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::vector<TAnchorBox> m_vecAnchor;

        cv::Size m_modelInputSize = cv::Size(192, 320);
        cv::Size m_outputBoxSize;
        cv::Size m_outputScoreSize;
        cv::Size m_outputLandmarkSize;
        cv::Size m_outputMasksSize;
        cv::Size m_outputClsSize;

        std::vector<std::pair<std::string, std::vector<int64_t>>> m_inputShape;
        std::vector<std::pair<std::string, std::vector<int64_t>>> m_outputShape;

        bool m_bDecode = true;
        float m_fScoreTh = 0.95f;
        float m_fNMSTh = 0.4f;
        size_t m_uiOutputTopK = 500;
        size_t m_uiNMSTopK = 50;
        std::unique_ptr <ICapacity_FaceDetection> m_pCapacityProcess = nullptr;

        cv::Mat m_blobImage;
};

}