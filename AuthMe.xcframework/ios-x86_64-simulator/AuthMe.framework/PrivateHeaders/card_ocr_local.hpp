#pragma once
#include "v3/card_ocr.hpp"
#include "card_detection.hpp"
#include "card_classification.hpp"
#include "reflection_detection.hpp"

namespace AuthMe
{

class CCardOCR : public ICardOCR
{
    public:
        CCardOCR();
        virtual ~CCardOCR();
        bool Initial(const AuthMeCardOCRModels& params) override;
        void SetUIParams(const AuthMeV3ServiceUIParams& params) override;
        AuthMeV3ServiceUIParams GetUIParams() const override;
        void SetParams(const AuthMeCardOCRParams& params) override;
        AuthMeCardOCRParams GetParams() const override;
        cv::Rect2f GetNormalizedROI() const override;
        void SetCardMatchNormalizedROI(const std::vector<cv::Point2f>& vecVertices) override;
        void SetCustomReflectiveROI(const std::vector<cv::Rect2f>& vecROI) override;
        AuthMeCardOCRResult Run(const cv::Mat& srcImage) override;

    private:
        void LoadModelDefaultParams();
        std::vector<cv::Rect2f> LoadDefaultReflectiveROI(EAuthMeCardClass eCardClass);
        void CalcROI();
        cv::Mat CenterCrop(const cv::Mat& image, float fRatio);

        std::unique_ptr<ICardDetection> m_pCardDetect;
        std::unique_ptr<ICardClassification> m_pCardClassify;
        std::unique_ptr<IReflectionDetection> m_pReflectDetect;

        AuthMeV3ServiceUIParams m_uiParams;
        AuthMeCardOCRParams m_params;

        cv::Rect m_analyzeROI;
        cv::Rect m_previewROI;
        cv::Rect2f m_normalizedROI;
        std::vector<cv::Point2f> m_vecCardMatchVertices;
        std::vector<cv::Rect2f> m_vecReflectiveROI;
};

}
