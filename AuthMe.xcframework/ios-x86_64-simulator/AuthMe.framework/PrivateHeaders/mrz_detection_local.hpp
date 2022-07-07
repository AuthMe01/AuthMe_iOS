#include "mrz_detection.hpp"
#include "nn_inference.hpp"
#include "mrz_detection_capacity.hpp"

namespace AuthMe
{

class CMRZDetection : public IMRZDetection
{
    public:
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") override;

        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;

        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;

        // input image for mat should be BGR
        std::vector<cv::Point2f>  Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, AuthMeEngineDebugInfo* pInfo = nullptr) override;

        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        cv::Mat Preprocess(const cv::Mat& inputImage);
        std::vector<cv::Point2f> Postprocess(const cv::Mat& matOutput, const cv::Size& targetSize);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::unique_ptr<ICapacity_MRZDetection> m_pCapacityProcess = nullptr;
};

}
