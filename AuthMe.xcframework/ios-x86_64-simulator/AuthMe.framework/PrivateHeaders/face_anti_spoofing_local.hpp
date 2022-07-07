#pragma once
#include "face_anti_spoofing.hpp"
#include "face_anti_spoofing_model.hpp"
#include "utility_moving_window.hpp"

namespace AuthMe
{

#define MOVING_AVG_DEFAULT_WINDOW_LENGTH 3

class CFaceAntiSpoofing : public IFaceAntiSpoofing
{
    public:
        CFaceAntiSpoofing(IFaceAntiSpoofing* pObj, bool bHold);
        virtual ~CFaceAntiSpoofing();
        virtual EAuthMeEngineReturnCode Initial(const std::string& strModelPath, const std::string strHWAcceleration) override;
        virtual EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration) override;
        virtual EAuthMeEngineReturnCode Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration) override;
        virtual void SetThreshold(float fThreshold) override;
        virtual float GetThreshold() const override;
        virtual void SetMinFrameNum(size_t uiLength) override;
        virtual size_t GetMinFrameNum() const override;
        virtual void Reset() override;
        virtual std::pair<EFaceAntiSpoofingStatus, float> Detect(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecLandmark, AuthMeEngineDebugInfo* pInfo = nullptr) override;
        virtual std::string GetModelInfo() const override;
        virtual double TableMapping(double dValue) const override;

    private:
        EAuthMeEngineReturnCode InitialSetup();

        CFaceAntiSpoofingModel* m_pObj = nullptr;
        bool m_bHold = false;

        float m_fScoreTh = 0.0f;
        CMovingWindow<float> m_ScoreWindow;
};

}
