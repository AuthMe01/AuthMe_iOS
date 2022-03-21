#pragma once
#include <string>
#include <vector>
#include <memory>
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

class IFaceAlignment : public IEngineBase
{
    public:
        virtual ~IFaceAlignment() {}

        // for encrypted and plaintext model
        virtual bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") = 0;

        // for encrypted model
        virtual bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") = 0;

        // for plaintext model
        virtual bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") = 0;

        virtual std::string GetModelInfo() const = 0;

        virtual std::vector<cv::Point2f> Run(const cv::Mat& inputImage, const cv::Rect2f& faceRect, cv::Mat* pResultImage = nullptr, TEngineDebugInfo* pInfo = nullptr) = 0;
};

void GetEyeStatus(const std::vector<cv::Point2f>& vecLandmarks, float &fScore, EEyeStatus &eStatus, float fThreshold = 0.2f);

void GetMouthStatus(const std::vector<cv::Point2f>& vecLandmarks, float &fScore, EMouthStatus &eStatus, float fThreshold = 0.5f);

IFaceAlignment* CreateFaceAlignment();

}
