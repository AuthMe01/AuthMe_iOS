#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

class IReflectionDetection: public IEngineBase
{
    public:
        virtual ~IReflectionDetection() {}

        // for encrypted and plaintext model
        virtual bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") = 0;

        // for encrypted model
        virtual bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") = 0;

        // for plaintext model
        virtual bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") = 0;

        virtual std::string GetModelInfo() const = 0;

        virtual void SetThreshold(float fThreshold) = 0;

        virtual float GetThreshold() const = 0;

        // input image for mat should be BGR, return mat type is CV_32F, range [0~1]
        // set vecVertices = {} if using whole image
        virtual cv::Mat Detect(const cv::Mat& inputImage, const std::vector<cv::Point>& vecVertices, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) = 0;
};

IReflectionDetection* CreateReflectionDetection();

// set vecROI = {} if using whole image
float CalcMaxReflectiveScore(const cv::Mat& matReflective, const std::vector<cv::Rect2f>& vecROI);

}
