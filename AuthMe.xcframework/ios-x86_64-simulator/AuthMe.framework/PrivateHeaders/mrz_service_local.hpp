#include "mrz_service.hpp"
#include "mrz_detection.hpp"
#include "mrz_recognition.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

class CMRZService : public IMRZService
{
    public:
        virtual bool Initial(const std::string& strDetModelPath,
                             const std::string& strRegModelPath,
                             const std::string strDetHWAcc = "cpu",
                             const std::string strRegHWAcc = "cpu") override;

        virtual bool Initial(const void *pDetData,
                             size_t uiDetLength,
                             const void *pRegData,
                             size_t uiRegLength,
                             const std::string strDetHWAcc = "cpu",
                             const std::string strRegHWAcc = "cpu") override;

        virtual bool Initial(const void *pDetData,
                             size_t uiDetLength,
                             EEngineFrameworkType eDetFramework,
                             const void *pRegData,
                             size_t uiRegLength,
                             EEngineFrameworkType eRegFramework,
                             const std::string strDetHWAcc = "cpu",
                             const std::string strRegHWAcc = "cpu") override;

        // input image for mat should be BGR
        virtual EMRZRecogStatus Run(const cv::Mat& inputImage,
                                    TMRZFieldTD3& tField,
                                    std::vector<cv::Point2f>& vecVertices,
                                    cv::Mat* pResultImage = nullptr,
                                    std::vector<TEngineDebugInfo>* pvecInfo = nullptr) override;

        virtual std::string GetModelInfo() const override;

    private:
        std::unique_ptr<IMRZDetection> pMRZDetect;
        std::unique_ptr<IMRZRecognition> pMRZRecog;
};

}