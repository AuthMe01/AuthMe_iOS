#pragma once
#include <string>
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

class IMRZService : public IEngineBase
{
    public:
        virtual ~IMRZService() {}

        virtual bool Initial(const std::string& strDetModelPath,
                             const std::string& strRegModelPath,
                             const std::string strDetHWAcc = "cpu",
                             const std::string strRegHWAcc = "cpu") = 0;

        virtual bool Initial(const void *pDetData,
                             size_t uiDetLength,
                             const void *pRegData,
                             size_t uiRegLength,
                             const std::string strDetHWAcc = "cpu",
                             const std::string strRegHWAcc = "cpu") = 0;

        virtual bool Initial(const void *pDetData,
                             size_t uiDetLength,
                             EEngineFrameworkType eDetFramework,
                             const void *pRegData,
                             size_t uiRegLength,
                             EEngineFrameworkType eRegFramework,
                             const std::string strDetHWAcc = "cpu",
                             const std::string strRegHWAcc = "cpu") = 0;

        // input image for mat should be BGR
        virtual EMRZRecogStatus Run(const cv::Mat& inputImage,
                                    TMRZFieldTD3& tField,
                                    std::vector<cv::Point2f>& vecVertices,
                                    cv::Mat* pResultImage = nullptr,
                                    std::vector<TEngineDebugInfo>* pvecInfo = nullptr) = 0;

        virtual std::string GetModelInfo() const = 0;
};

IMRZService* CreateMRZService();

}