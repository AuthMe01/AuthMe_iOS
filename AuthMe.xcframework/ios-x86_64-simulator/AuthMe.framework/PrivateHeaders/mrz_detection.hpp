#pragma once
#include <string>
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

class IMRZDetection : public IEngineBase
{
    public:
        virtual ~IMRZDetection() {}

        // for encrypted and plaintext model
        virtual bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") = 0;

        // for encrypted model
        virtual bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") = 0;

        // for plaintext model
        virtual bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") = 0;

        // input image for mat should be BGR
        virtual std::vector<cv::Point2f> Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) = 0;

        virtual std::string GetModelInfo() const = 0;
};

IMRZDetection* CreateMRZDetection();

}