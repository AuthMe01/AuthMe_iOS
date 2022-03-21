#pragma once
#include "id_card_anti_fraud_service.hpp"
#include "card_detection.hpp"
#include "card_classification.hpp"
#include "laser_tag_detection.hpp"
#include "taiwan_hole_detection.hpp"
#include "metal_tag_detection.hpp"
#include "v3_base.hpp"

namespace AuthMe
{

class CIDCardAntiFraudService : public IIDCardAntiFraudService, protected CBaseV3
{
    public:
        CIDCardAntiFraudService();
        virtual ~CIDCardAntiFraudService();
        bool Initial(const AuthMeIDCardAntiFraudServiceModels& params) override;
        void SetUIParams(const AuthMeV3ServiceUIParams& params) override;
        AuthMeV3ServiceUIParams GetUIParams() const override;
        void SetParams(const AuthMeIDCardAntiFraudParams& params) override;
        AuthMeIDCardAntiFraudParams GetParams() const override;
        cv::Rect2f GetNormalizedROI() const override;
        void SetCardMatchNormalizedROI(const std::vector<cv::Point2f>& vecVertices) override;
        void Start() override;
        AuthMeIDCardAntiFraudResult Run(const cv::Mat& srcImage) override;

    private:
        void LoadModelDefaultParams();
        void CalcROI();
        std::pair<EAuthMeCardMatchStatus, float> CalcCardMatch(const std::vector<cv::Point>& vecVertices);
        int GetValidMetalTagCount(const std::vector<MetalTagReturnType>& vecResults);
        bool MeetConditions(const AuthMeIDCardAntiFraudStatistics& statistics);
        cv::Mat CenterCrop(const cv::Mat& image, float fRatio);
        void SetMetalTagInfo(AuthMeMetalTagInfo& info, const std::vector<MetalTagReturnType>& vecResult, const cv::Point& shift, const cv::Mat& matrix);


        std::unique_ptr<ICardDetection> m_pCardDetect;
        std::unique_ptr<ICardClassification> m_pCardClassify;
        std::unique_ptr<ILaserTagDetection> m_pLaserTagDetect;
        std::unique_ptr<ITaiwanHoleDetection> m_pTaiwanHoleDetect;
        std::unique_ptr<IMetalTagDetection> m_pMetalTagDetect;

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
};

}