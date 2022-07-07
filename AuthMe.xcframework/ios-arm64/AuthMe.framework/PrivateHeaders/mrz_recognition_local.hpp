#include "mrz_recognition.hpp"
#include "nn_inference.hpp"
#include "mrz_recognition_capacity.hpp"

namespace AuthMe
{

class CMRZRecognition : public IMRZRecognition
{
    public:
        EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") override;

        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;

        EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;

        // input image for mat should be BGR
        EMRZRecogStatus Run(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecVertices, TMRZFieldTD3& tField, AuthMeEngineDebugInfo* pInfo = nullptr) override;

        std::string GetModelInfo() const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();
        EAuthMeEngineReturnCode GetParamsFromModel();
        cv::Mat Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecVertices);
        bool Postprocess(const std::vector<int64_t>& vecOutput, TMRZFieldTD3& tField);

        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
        std::unique_ptr<ICapacity_MRZRecognition> m_pCapacityProcess = nullptr;
};

}