#pragma once
#include "face_alignment.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

class CFaceAlignment : public IFaceAlignment
{
    public:
        bool Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;
        std::string GetModelInfo() const override;
        std::vector<cv::Point2f> Run(const cv::Mat& inputImage, const cv::Rect2f& faceRect, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) override;

    private:
        void Preprocess(const cv::Mat& inputImage, const cv::Rect2f& faceRect, cv::Mat& matModelInput, cv::Mat& transMatrix);
        std::vector<cv::Point2f> PostProcess(const std::vector<float>& vecModelOutput, const cv::Mat& transMatrix);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
};

}

