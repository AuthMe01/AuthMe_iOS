#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

typedef enum
{
    eFaceAntiSpoofing_FrameNotEnough,
    eFaceAntiSpoofing_Real,
    eFaceAntiSpoofing_Spoof,
} EFaceAntiSpoofingStatus;

class IFaceAntiSpoofing : public IEngineBase
{
    public:
        virtual ~IFaceAntiSpoofing() {}

        // for encrypted and plaintext model
        virtual bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") = 0;

        // for encrypted model
        virtual bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") = 0;

        // for plaintext model
        virtual bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") = 0;

        virtual void SetThreshold(float fThreshold) = 0;

        virtual float GetThreshold() const = 0;

        virtual void SetMinFrameNum(size_t uiLength) = 0;

        virtual size_t GetMinFrameNum() const = 0;

        virtual void Reset() = 0;

        // input image for mat should be BGR
        virtual EFaceAntiSpoofingStatus Detect(const cv::Mat& matImage, const std::vector<cv::Point2f>& vecLandmark, float& fScore, TEngineDebugInfo* pInfo = nullptr) = 0;

        virtual std::string GetModelInfo() const = 0;
};

IFaceAntiSpoofing* CreateFaceAntiSpoofing();

}