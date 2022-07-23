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
        cv::Rect2f GetNormalizedROI() const override;
        void SetCardMatchNormalizedROI(const std::vector<cv::Point2f>& vecVertices) override;
        void Start() override;
        AuthMeIDCardAntiFraudResult Run(const cv::Mat& srcImage) override;
        EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) override;

    private:
        void LoadModelDefaultParams();
        void CalcROI();
        std::pair<EAuthMeCardMatchStatus, float> CalcCardMatch(const std::vector<cv::Point>& vecVertices);
        int GetValidMetalTagCount(const std::vector<MetalTagReturnType>& vecResults);
        bool MeetConditions(const AuthMeIDCardAntiFraudStatistics& statistics);
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
        cv::Size m_IdealCardSize = {760, 480};

        int iCardMatchCount = 0;
        AuthMeIDCardAntiFraudStatistics m_statistics;
        std::vector<int> m_vecMetalTagStatus;
        std::vector<AuthMeEngineDebugInfo> m_vecDebugInfo;
        std::vector<cv::Point2f> m_vecCardVertices;
        AuthMeIDCardAntiFraudInfo m_info;
};

}