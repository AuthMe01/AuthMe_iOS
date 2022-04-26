#pragma once
#include <string>
#include <vector>
#include <memory>
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

class IFaceDetection : public IEngineBase
{
    public:
        virtual ~IFaceDetection() {}

        // for encrypted and plaintext model
        virtual bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") = 0;

        // for encrypted model
        virtual bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") = 0;

        // for plaintext model
        virtual bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") = 0;

        virtual void SetThreshold(float fThreshold) = 0;

        virtual float GetThreshold() const = 0;

        virtual void SetInferenceSize(const cv::Size& inferSize) = 0;

        // input image for mat should be BGR
        virtual std::vector<TFaceInfo> Detect(const cv::Mat& inputImage, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) = 0;

        virtual std::string GetModelInfo() const = 0;
};

EFacePose GetFacePose(const std::vector<cv::Point2f>& vecLandmarks);

float GetDistanceToPose(const std::vector<cv::Point2f>& vecLandmarks, EFacePose ePose);

IFaceDetection* CreateFaceDetection();

}