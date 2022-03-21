#pragma once
#include "v3/fas_service.hpp"
#include "face_detection.hpp"
#include "face_alignment.hpp"
#include "face_anti_spoofing.hpp"
#include "v3_base.hpp"

namespace AuthMe
{

class CFASService_Base : public IFASService, protected CBaseV3
{
    public:
        CFASService_Base();
        virtual ~CFASService_Base() {}
        virtual bool Initial(const AuthMeFASServiceModels& params) override;
        virtual void SetUIParams(const AuthMeV3ServiceUIParams& params) override;
        virtual AuthMeV3ServiceUIParams GetUIParams() override;
        virtual void SetParams(const AuthMeFASParams& param) override;
        virtual AuthMeFASParams GetParams() override;
        virtual cv::Rect2f GetNormalizedFaceROI() override;
        virtual void Start() override;

    protected:
        void CalcFaceROI(const AuthMeV3ServiceUIParams& uiParams,
                         const float fFaceROIRatioW,
                         const float fFaceROIRatioH,
                         const AuthMePointFloat& shift);
        void GetModelDefaultParams();
        AuthMeFASResult CheckQualifiedFace(const cv::Mat& inputImage,
                                           EAuthMeFASServiceStage eCurrentStage,
                                           EAuthMeMouthStatus eTargetMouthStatus);
        bool IsNotAtCenter(const cv::Rect2f& faceRect);
        bool IsFaceTooSmall(const cv::Rect2f& faceRect);
        bool IsFaceTooLarge(const cv::Rect2f& faceRect);
        bool IsNotFaceToCamera(EAuthMeFacePose ePose);
        bool IsFaceMasked(const float fMaskScore);

        std::unique_ptr<IFaceDetection> m_pFaceDetect;
        std::unique_ptr<IFaceAlignment> m_pFaceAlignment;
        std::unique_ptr<IFaceAntiSpoofing> m_pFAS;


        cv::Size m_analyzeSize;
        cv::Rect2f m_normalizedFaceRoi;
        cv::Rect2f m_faceRoi;
        AuthMeV3ServiceUIParams m_uiParams;
        AuthMeFASParams m_params;
};

AuthMeRectFloat Convert(const cv::Rect2f& input);
AuthMeFaceInfo Convert(const TFaceInfo& input);

}