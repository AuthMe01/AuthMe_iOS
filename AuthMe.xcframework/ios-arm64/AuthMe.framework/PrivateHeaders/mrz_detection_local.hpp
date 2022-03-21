#include "mrz_detection.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

class CMRZDetection : public IMRZDetection
{
    public:
        bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") override;

        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;

        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;

        // input image for mat should be BGR
        std::vector<cv::Point2f>  Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) override;

        std::string GetModelInfo() const override;

    private:
        cv::Mat Preprocess(const cv::Mat& inputImage);
        std::vector<cv::Point2f> Postprocess(const cv::Mat& matOutput, const cv::Size& targetSize);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
};

}