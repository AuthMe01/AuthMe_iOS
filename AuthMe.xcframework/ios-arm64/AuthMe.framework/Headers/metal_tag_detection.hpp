#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

using MetalTagReturnType = std::pair<EIDCardMetalTagStatus, std::vector<cv::Point>>;

class IMetalTagDetection : public IEngineBase
{
    public:
        virtual ~IMetalTagDetection() {}

        // for encrypted and plaintext model
        virtual bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") = 0;

        // for encrypted model
        virtual bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") = 0;

        // for plaintext model
        virtual bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") = 0;

        virtual void SetThreshold(float fThreshold) = 0;

        virtual float GetThreshold() const = 0;

        // input image for mat should be BGR
        virtual std::vector<MetalTagReturnType> Detect(const cv::Mat& inputImage, const std::vector<cv::Point>& vecVertices, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) = 0;

        virtual std::string GetModelInfo() const = 0;
};

IMetalTagDetection* CreateMetalTagDetection();

}