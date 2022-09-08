#pragma once
#include "fas_service.hpp"
#include "face_detection.hpp"
#include "face_alignment.hpp"
#include "face_anti_spoofing.hpp"
#include "mini_fas.hpp"
#include "service_base.hpp"

namespace AuthMe
{

typedef struct FAS_FRAME_REPORT_OBJECT
{
    EAuthMeFASServiceStage eStage;
    EAuthMeFASServiceStatus eStatus;
} FASFrameReportObject;

typedef struct FAS_STAGE_REPORT_OBJECT
{
    EAuthMeFASServiceStage eStage;
    EAuthMeFASServiceStatus eStatus;
    int iFrameIndex = 0;
} FASStageReportObject;

typedef struct FAS_SERVICE_RECORD
{
    std::string strJson;
    int iFrameIndex = 0;
    float fMaxFASScore = 0.0f;
    std::vector<FASFrameReportObject> vecFrameRecord;
    std::vector<FASStageReportObject> vecStageRecord;
} FASServiceRecord;

class IFASService_Stage;

class CFASService : public IFASService, protected CServiceBase
{
    public:
        CFASService();
        virtual ~CFASService() {}
        std::vector<AuthMeEngineDebugInfo> &GetDeBugInfo() override;
        bool Initial(const AuthMeFASServiceModels& models) override;
        void SetUIParams(const AuthMeV3ServiceUIParams& params) override;
        AuthMeV3ServiceUIParams GetUIParams() const override;
        void SetParams(const AuthMeFASParams& param) override;
        AuthMeFASParams GetParams() const override;
        cv::Rect2f GetNormalizedFaceROI() const override;
        void SetStage(const std::vector<EAuthMeFASServiceStage>& vecStage) override;
        std::vector<EAuthMeFASServiceStage> GetStage() const override;
        void SetStageParams(const AuthMeFASStageParams& params, int iIndex) override;
        AuthMeFASStageParams GetStageParams(int iIndex) const override;
        EAuthMeEngineReturnCode Start() override;
        AuthMeFASResult Run(const cv::Mat& inputImage) override;
        EAuthMeEngineReturnCode Stop() override;
        const std::string& GetJsonReport() override;
        EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) override;

    protected:
        AuthMeFASResult RunImpl(const cv::Mat& inputImage);
        void UpdateRecord(const AuthMeFASResult& result);
        std::shared_ptr<IFASService_Stage> GetStageModule(EAuthMeFASServiceStage eStage);
        void CalcFaceROI(const AuthMeV3ServiceUIParams& uiParams,
                         const float fFaceROIRatioW,
                         const float fFaceROIRatioH,
                         const AuthMePointFloat& shift);
        void GetModelDefaultParams();
        void ResetStage();
        void GenFaceInfo(const cv::Mat& inputImage, AuthMeFASResult& result, std::vector<cv::Point2f>& vecLandmark106);

        friend class CStageBase;

        IFaceDetection* m_pFaceDetect = nullptr;
        IFaceAlignment* m_pFaceAlignment = nullptr;
        IFaceAntiSpoofing* m_pFAS = nullptr;
        IMiniFAS* m_pMiniFAS = nullptr;

        std::vector<std::pair<EAuthMeFASServiceStage, std::shared_ptr<IFASService_Stage>>> m_vecStageSet;
        std::vector<std::pair<EAuthMeFASServiceStage, std::shared_ptr<IFASService_Stage>>>::iterator m_pStage;
        std::vector<AuthMeFASStageParams> m_vecStageParams;
        cv::Size m_analyzeSize;
        cv::Rect2f m_normalizedFaceRoi;
        cv::Rect2f m_faceRoi;
        cv::Rect2f m_previewRoi;
        AuthMeV3ServiceUIParams m_uiParams;
        AuthMeFASParams m_params;
        std::vector<AuthMeEngineDebugInfo> m_vecDebugInfo;

        FASServiceRecord m_record;
};

AuthMeRectFloat Convert(const cv::Rect2f& input);
AuthMeFaceInfo Convert(const TFaceInfo& input);

}