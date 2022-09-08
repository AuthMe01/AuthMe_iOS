#pragma once
#include "id_card_anti_fraud_service.hpp"
#include "card_detection.hpp"
#include "card_classification.hpp"
#include "laser_tag_detection.hpp"
#include "taiwan_hole_detection.hpp"
#include "metal_tag_detection.hpp"
#include "service_base.hpp"
#include "reflection_detection.hpp"

namespace AuthMe
{

typedef struct ID_CARD_ANTI_FRAUD_FRAME_REPORT_OBJECT
{
    EAuthMeIDCardAntiFraudStage eStage;
    EAuthMeIDCardAntiFraudStatus eStatus;
} IDCardAntiFraudFrameReportObject;

typedef struct ID_CARD_ANTI_FRAUD_STAGE_REPORT_OBJECT
{
    EAuthMeIDCardAntiFraudStage eStage;
    EAuthMeIDCardAntiFraudStatus eStatus;
    int iFrameIndex = 0;
} IDCardAntiFraudStageReportObject;

typedef struct ID_CARD_ANTI_FRAUD_SERVICE_RECORD
{
    std::string strJson;
    int iFrameIndex = 0;
    float fMaxScore = 0.0f;
    std::vector<IDCardAntiFraudFrameReportObject> vecFrameRecord;
    std::vector<IDCardAntiFraudStageReportObject> vecStageRecord;
} IDCardAntiFraudServiceRecord;

class CIDCardAntiFraudService : public IIDCardAntiFraudService, protected CServiceBase
{
    public:
        CIDCardAntiFraudService();
        virtual ~CIDCardAntiFraudService();
        const std::vector<AuthMeEngineDebugInfo>& GetDeBugInfo() override;
        bool Initial(const AuthMeIDCardAntiFraudServiceModels& models) override;
        void SetUIParams(const AuthMeV3ServiceUIParams& params) override;
        AuthMeV3ServiceUIParams GetUIParams() const override;
        void SetParams(const AuthMeIDCardAntiFraudParams& params) override;
        AuthMeIDCardAntiFraudParams GetParams() const override;
        void SetStage(const std::vector<EAuthMeIDCardAntiFraudStage>& vecStage) override;
        std::vector<EAuthMeIDCardAntiFraudStage> GetStage() const override;
        cv::Rect2f GetAnalysisROI() const override;
        void SetFrontalCardVertices(const std::vector<cv::Point2f>& vecVertices) override;
        std::vector<cv::Point2f> GetCardMatchROI() override;
        EAuthMeEngineReturnCode Start() override;
        AuthMeIDCardAntiFraudResult Run(const cv::Mat& srcImage) override;
        EAuthMeEngineReturnCode Stop() override;
        const std::string& GetJsonReport() override;
        EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) override;

    private:
        void LoadModelDefaultParams();
        void SetPass();
        AuthMeIDCardAntiFraudResult RunImpl(const cv::Mat& srcImage);
        void UpdateRecord(const AuthMeIDCardAntiFraudResult& result);
        EAuthMeIDCardAntiFraudStage GetNextStage();
        void SetCardMatchStage(EAuthMeIDCardAntiFraudStage eStage);
        void UpdateCardMatchPoints(EAuthMeIDCardAntiFraudStage eStage);
        std::vector<cv::Point2f> CalcCardMatchPoints(const cv::Point3f& axis, const float degree);
        void CalcROI();
        std::pair<EAuthMeCardMatchStatus, float> CalcCardMatch(const std::vector<cv::Point>& vecVertices);
        int GetValidMetalTagCount(const std::vector<MetalTagReturnType>& vecResults);
        bool MeetConditions(const AuthMeIDCardAntiFraudStatistics& statistics);
        bool CardMatchPassed(const AuthMeIDCardAntiFraudInfo& info);
        cv::Mat CenterCrop(const cv::Mat& image, float fRatio);
        void SetMetalTagInfo(AuthMeMetalTagInfo& info, const std::vector<MetalTagReturnType>& vecResult, const cv::Point& shift, const cv::Mat& matrix);

        ICardDetection* m_pCardDetect = nullptr;
        ICardClassification* m_pCardClassify = nullptr;
        ILaserTagDetection* m_pLaserTagDetect = nullptr;
        ITaiwanHoleDetection* m_pTaiwanHoleDetect = nullptr;
        IMetalTagDetection* m_pMetalTagDetect = nullptr;
        IReflectionDetection* m_pReflectDetect = nullptr;

        AuthMeV3ServiceUIParams m_uiParams;
        AuthMeIDCardAntiFraudParams m_params;

        cv::Rect m_analyzeROI;
        cv::Rect m_previewROI;
        cv::Rect2f m_normalizedROI;
        std::vector<cv::Point2f> m_vecCardMatchVertices;
        std::vector<cv::Point2f> m_vecCardMatchVerticesFrontal;
        std::vector<cv::Point2f> m_vecCardMatchVerticesLast;
        cv::Size m_IdealCardSize = {760, 480};
        EAuthMeIDCardAntiFraudStage m_currentStage;
        std::vector<EAuthMeIDCardAntiFraudStage> m_vecStage;
        int m_iStageIdx = -1;

        int iCardMatchCount = 0;
        AuthMeIDCardAntiFraudStatistics m_statistics;
        std::vector<int> m_vecMetalTagStatus;
        std::vector<AuthMeEngineDebugInfo> m_vecDebugInfo;
        IDCardAntiFraudServiceRecord m_record;
        std::vector<cv::Point2f> m_vecCardVertices;
        AuthMeIDCardAntiFraudInfo m_info;
};

}