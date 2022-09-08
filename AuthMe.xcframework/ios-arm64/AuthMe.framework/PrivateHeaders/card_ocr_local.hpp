#pragma once
#include "card_ocr_service.hpp"
#include "service_base.hpp"
#include "card_detection.hpp"
#include "card_classification.hpp"
#include "reflection_detection.hpp"

namespace AuthMe
{

typedef struct CARD_OCR_FRAME_REPORT_OBJECT
{
    EAuthMeCardOCRStatus eStatus;
} CardOCRFrameReportObject;

typedef struct CARD_OCR_SERVICE_RECORD
{
    std::string strJson;
    std::vector<CardOCRFrameReportObject> vecFrameRecord;
} CardOCRServiceRecord;

class CCardOCR : public ICardOCRService, protected CServiceBase
{
    public:
        CCardOCR();
        virtual ~CCardOCR();
        const std::vector<AuthMeEngineDebugInfo> &GetDeBugInfo() override;
        bool Initial(const AuthMeCardOCRModels& models) override;
        void SetUIParams(const AuthMeV3ServiceUIParams& params) override;
        AuthMeV3ServiceUIParams GetUIParams() const override;
        void SetParams(const AuthMeCardOCRParams& params) override;
        AuthMeCardOCRParams GetParams() const override;
        cv::Rect2f GetAnalysisROI() const override;
        void SetCardMatchROI(const std::vector<cv::Point2f>& vecVertices) override;
        void SetCustomReflectiveROI(const std::vector<cv::Rect2f>& vecROI) override;
        EAuthMeEngineReturnCode Start() override;
        AuthMeCardOCRResult Run(const cv::Mat& srcImage) override;
        EAuthMeEngineReturnCode Stop() override;
        const std::string& GetJsonReport() override;
        EAuthMeEngineReturnCode GetDebugImage(cv::Mat& image) override;

    private:
        AuthMeCardOCRResult RunImpl(const cv::Mat& srcImage);
        void LoadModelDefaultParams();
        std::vector<cv::Rect2f> LoadDefaultReflectiveROI(EAuthMeCardClass eCardClass);
        void CalcROI();
        cv::Mat CenterCrop(const cv::Mat& image, float fRatio);

        ICardDetection* m_pCardDetect = nullptr;
        ICardClassification* m_pCardClassify = nullptr;
        IReflectionDetection* m_pReflectDetect = nullptr;

        AuthMeV3ServiceUIParams m_uiParams;
        AuthMeCardOCRParams m_params;

        cv::Rect m_analyzeROI;
        cv::Rect m_previewROI;
        cv::Rect2f m_normalizedROI;
        std::vector<cv::Point2f> m_vecCardMatchVertices;
        std::vector<cv::Rect2f> m_vecReflectiveROI;
        std::vector<AuthMeEngineDebugInfo> m_vecDebugInfo;

        CardOCRServiceRecord m_record;
        std::vector<cv::Point2f> m_vecCardVertices;
        AuthMeCardOCRInfo m_info = {};
};

}
