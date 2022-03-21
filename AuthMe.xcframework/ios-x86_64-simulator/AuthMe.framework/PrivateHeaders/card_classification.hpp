#pragma once
#include <string>
#include <vector>
#include <memory>
#include "opencv2/core.hpp"
#include "engine_base.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

typedef enum _E_CARD_CLASS : int
{
    eCard_Invalid = -1,
    eCard_Background = 0,
    eCard_Unknown,
    eCard_Passport,
    eCard_TWN_IDCard_Front,
    eCard_TWN_IDCard_Back,
    eCard_TWN_DriverLicense_Front,
    eCard_TWN_DriverLicense_Back,
    eCard_TWN_Resident_Front,
    eCard_TWN_Resident_Back,
    eCard_TWN_Health_Front,
    eCard_TWN_VehiclesLicense_Front,
} ECardClass;

class ICardClassification : public IEngineBase
{
    public:
        virtual ~ICardClassification() {}

        // for encrypted and plaintext model
        virtual bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") = 0;

        // for encrypted model
        virtual bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") = 0;

        // for plaintext model
        virtual bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") = 0;

        virtual void SetThreshold(const float fThreshold) = 0;

        virtual float GetThreshold() const = 0;

        // input image for mat should be BGR
        virtual ECardClass Run(const cv::Mat& matImage, const std::vector<cv::Point2i>& vecPolygon, TEngineDebugInfo* pInfo = nullptr) = 0;

        virtual std::string GetModelInfo() const = 0;
};

ICardClassification* CreateCardClassification();

}