#pragma once
#include "engine_service_type.h"
#include "opencv2/core.hpp"
#include <chrono>

namespace AuthMe
{

typedef enum E_ANALYSIS_ROI_TYPE
{
    eAuthMe_ROIType_Preview,
    eAuthMe_ROIType_CenterCrop,
    eAuthMe_ROIType_FullImage,
} EAnalysisROIType;

typedef struct SERVICE_BASIC_FUNCTION_SETTINGS
{
    bool bEnableAlgoLog = true;
} ServiceBasicFunctionSettings;

class CServiceBase
{
    public:
        CServiceBase();
        virtual ~CServiceBase();

    protected:
        void SetTimeoutTime(int iSec);
        bool Start();
        bool Stop();
        bool IsRunning() const;
        bool IsAlreadyPass() const;
        void SetPass();
        void SetFail();
        bool IsFail() const;
        bool IsTimeout() const;
        void SetFunctions(const ServiceBasicFunctionSettings& settings);
        ServiceBasicFunctionSettings GetFunctions() const;
        bool IsJsonCryptionEnabled() const;

        void SetAnalysisROIType(EAnalysisROIType eType);
        void UpdateUIParams(const AuthMeServiceUIParams& params);
        const AuthMeServiceUIParams& GetUIParamsRef() const;

    private:
        void UpdateAnalyzeROI();
        cv::Rect CalcAnalyzeROI_Preview();
        cv::Rect CalcAnalyzeROI_FullImage();
        cv::Rect CalcAnalyzeROI_CenterCrop();

    protected:
        cv::Rect m_analyzeROI;
        cv::Rect m_previewROI;
        cv::Rect2f m_normalizedAnalysisROI;

    private:
        bool m_bIsRunning = false;
        bool m_bPass = false;
        bool m_bFail = false;
        int m_iTimeoutSec = 0;
        std::chrono::time_point<std::chrono::system_clock> m_startTime;

        AuthMeServiceUIParams m_uiParams;
        ServiceBasicFunctionSettings m_functionSettings;
        EAnalysisROIType m_eROIType = eAuthMe_ROIType_FullImage;
};

}
