#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_type.h"
#include "engine_base.h"
#include <stdbool.h>

// c an c++ shared structures and types

#define IMPL_VAR(type, name) type name;


typedef struct AUTHME_MODEL_VERSION
{
    char szName[32];
    char szVersion[8];
} AuthMeModelVersion;


#define CARD_MATCH_STATUS_TAG(decorate) \
    decorate(Mismatch) \
    decorate(NeedMoreFrame) \
    decorate(CardNotInAnalysisROI) \
    decorate(CardNotInROI) \
    decorate(CardTooSmall) \
    decorate(NeedMoreDeformation) \
    decorate(NeedHoldCard) \
    decorate(None) \
    decorate(Match)
//
//#define CARD_MATCH_STATUS_PREFIX(name) eAuthMe_CardMatch_##name,
typedef enum E_AUTHME_CARD_MTACH_STATUS
{
    eAuthMe_CardMatch_Mismatch,
    eAuthMe_CardMatch_NeedMoreFrame,
    eAuthMe_CardMatch_CardNotInAnalysisROI,
    eAuthMe_CardMatch_CardNotInROI,
    eAuthMe_CardMatch_CardTooSmall,
    eAuthMe_CardMatch_NeedMoreDeformation,
    eAuthMe_CardMatch_NeedHoldCard,
    eAuthMe_CardMatch_None,
    eAuthMe_CardMatch_Match,
} EAuthMeCardMatchStatus;


typedef struct AUTHME_FAS_SERVICE_MODELS
{
    long FACE_00;
    long FACE_01;
    long FACE_02;
    long FACE_03;
} AuthMeFASServiceModels;

#define SERVICE_UI_PARAMS_CONTENT(decorate) \
    decorate(int, mirrorDisplay) /* 0: disabled, 1: enabled */ \
    decorate(AuthMeSize, analyzeSize) /* pixel */ \
    decorate(AuthMeRectFloat, previewPosition) /* l, t, r, b in range [0~1] */

typedef struct AUTHME_SERVICE_UI_PARAMS
{
    int mirrorDisplay; 
    AuthMeSize analyzeSize;
    AuthMeRectFloat previewPosition;
    DEFAULT_COMPARISON(AUTHME_SERVICE_UI_PARAMS)
} AuthMeServiceUIParams;

typedef struct AUTHME_EYE_INFO
{
    EAuthMeEyeStatus eStatus;
    float fScore;
    DEFAULT_COMPARISON(AUTHME_EYE_INFO);
} AuthMeEyeInfo;

typedef struct AUTHME_MOUTH_INFO
{
    EAuthMeMouthStatus eStatus;
    float fScore;
    DEFAULT_COMPARISON(AUTHME_MOUTH_INFO);
} AuthMeMouthInfo;

typedef struct AUTHME_FACE_POSE_INFO
{
    EAuthMeFacePose ePose;
    DEFAULT_COMPARISON(AUTHME_FACE_POSE_INFO)
} AuthMeFacePoseInfo;

typedef struct AUTHME_MINI_FAS_INFO
{
    EAuthMeFaceAntiSpoofingStatus eStatus;
    float fScore;
    DEFAULT_COMPARISON(AUTHME_MINI_FAS_INFO);
} AuthMeMiniFASInfo;

typedef struct AUTHME_FAS_INFO
{
    EAuthMeFaceAntiSpoofingStatus eStatus;
    int iClassNum;
    float afScore[20];
    float afAccumulateScore[20];
    float fDepthScore;
    DEFAULT_COMPARISON(AUTHME_FAS_INFO);
} AuthMeFASInfo;

typedef struct AUTHME_FAS_STAGE_PARAMS
{
    int applyFAS;
    int iFrameNum;
    float fThreshold;
    DEFAULT_COMPARISON(AUTHME_FAS_STAGE_PARAMS);
} AuthMeFASStageParams;

#define FAS_SERVICE_PARAMS_CONTENT(decorate) \
    /* algo params */ \
    decorate(float, fFaceDetectTh) \
    decorate(float, fMaskTh) \
    decorate(float, fEyeTh) \
    decorate(float, fMouthTh) \
    decorate(float, fFASTh) \
    decorate(int, iDepthLevel) \
    decorate(float, fMiniFASTh) \
    decorate(int, iFASAccumulativeNum) \
    /* other params */ \
    decorate(int, timeoutSec) \
    decorate(int, fasTimeoutSec) \
    decorate(AuthMeRectFloat, faceROI) \
    decorate(float, fNotAtCenterTh) \
    decorate(float, fFaceTooSmallTh) \
    decorate(float, fFaceTooLargeTh)

typedef struct AUTHME_FAS_PARAMS
{
    float fFaceDetectTh;
    float fMaskTh;
    float fEyeTh;
    float fMouthTh;
    float fFASTh;
    int iDepthLevel;
    float fMiniFASTh;
    int iFASAccumulativeNum;
    int timeoutSec;
    int fasTimeoutSec;
    AuthMeRectFloat faceROI;
    float fNotAtCenterTh;
    float fFaceTooSmallTh;
    float fFaceTooLargeTh;
    DEFAULT_COMPARISON(AUTHME_FAS_PARAMS);
} AuthMeFASParams;

typedef struct AUTHME_FAS_SERVICE_INFO
{
    AuthMeFaceInfo face;
    float afLandmark106[212];
    AuthMeEyeInfo eye;
    AuthMeMouthInfo mouth;
    AuthMeFacePoseInfo pose;
    AuthMeMiniFASInfo miniFAS;
    AuthMeFASInfo fas;
    DEFAULT_COMPARISON(AUTHME_FAS_SERVICE_INFO);
} AuthMeFASServiceInfo;

#define FAS_SERVICE_STATUS_TAG(decorate) \
    decorate(Failed) \
    decorate(NoFace) \
    decorate(FaceNotAtCenter) \
    decorate(FaceTooSmall) \
    decorate(FaceTooLarge) \
    decorate(NeedFaceToCamera) \
    decorate(FaceMasked) \
    decorate(NeedOpenMouth) \
    decorate(NeedCloseMouth) \
    decorate(NeedOpenEyes) \
    decorate(NeedSmile) \
    decorate(DepthFake) \
    decorate(NeedMoreFrame) \
    decorate(Pass) \
    decorate(Error)

//#define FAS_SERVICE_STATUS_PREFIX(name) eAuthMe_FASService_##name,
typedef enum E_AUTHME_FAS_SERVICE_STATUS
{
    eAuthMe_FASService_Failed,
    eAuthMe_FASService_NoFace,
    eAuthMe_FASService_FaceNotAtCenter,
    eAuthMe_FASService_FaceTooSmall,
    eAuthMe_FASService_FaceTooLarge,
    eAuthMe_FASService_NeedFaceToCamera,
    eAuthMe_FASService_FaceMasked,
    eAuthMe_FASService_NeedOpenMouth,
    eAuthMe_FASService_NeedCloseMouth,
    eAuthMe_FASService_NeedOpenEyes,
    eAuthMe_FASService_NeedSmile,
    eAuthMe_FASService_DepthFake,
    eAuthMe_FASService_NeedMoreFrame,
    eAuthMe_FASService_Pass,
    eAuthMe_FASService_Error,
} EAuthMeFASServiceStatus;


//const int FAS_SERVICE_STAGE_START_LINE = __LINE__;
#define FAS_SERVICE_STAGE_TAG(decorate) \
    decorate(Passive) \
    decorate(OpenMouth) \
    decorate(CloseMouth) \
    decorate(Smile) \
    decorate(FaceScale) \
    decorate(Done)
//const int iAuthMeFASServiceStageCount = __LINE__ - FAS_SERVICE_STAGE_START_LINE - 2;
//
//#define FAS_SERVICE_STAGE_PREFIX(name) eAuthMe_FASService_Stage_##name,
typedef enum E_AUTHME_FAS_SERVICE_STAGE
{
    eAuthMe_FASService_Stage_Passive, 
    eAuthMe_FASService_Stage_OpenMouth, 
    eAuthMe_FASService_Stage_CloseMouth, 
    eAuthMe_FASService_Stage_Smile, 
    eAuthMe_FASService_Stage_FaceScale, 
    eAuthMe_FASService_Stage_Done,
} EAuthMeFASServiceStage;

typedef struct AUTHME_FAS_RESULT
{
    int iIsKeyFrame;
    float fStageScore;
    AuthMeFASServiceInfo info;
    EAuthMeFASServiceStatus eStatus;
    EAuthMeFASServiceStage eStage;
    DEFAULT_COMPARISON(AUTHME_FAS_RESULT);
} AuthMeFASResult;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_MODELS
{
    long OCR_00;
    long OCR_01;
    long OCR_01_FB;
    long IDCardAntiFraud_00;
    long OCR_03;
} AuthMeIDCardAntiFraudServiceModels;

#define ID_CARD_ANTI_FRAUD_SERVICE_PARAMS_CONTENT(decorate) \
    /* algo params */ \
    decorate(float, fCardClassificationTh) \
    decorate(float, fMetalTagDetectionTh) \
    decorate(float, fImageReflectiveTh) \
    decorate(float, fImageBlurTh) \
    decorate(float, fImageThicknessTh) \
    decorate(float, fIDCardColorTh) \
    /* other params */ \
    decorate(int, timeoutSec) \
    decorate(int, iMetalTagValidCountTh) \
    decorate(int, enableCardInROI) \
    decorate(int, iCardMatchFrameNum) \
    decorate(float, fCardMatchTh) \
    decorate(float, fCardDeformationTh) \
    decorate(float, fMetalTagReflectionTh) \
    decorate(float, fMetalTagReflectionDensityTh)

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_PARAMS
{
    float fCardClassificationTh;
    float fMetalTagDetectionTh;
    float fImageReflectiveTh;
    float fImageBlurTh;
    float fImageThicknessTh;
    float fIDCardColorTh;
    int timeoutSec; 
    int iMetalTagValidCountTh;
    int enableCardInROI; 
    int iCardMatchFrameNum;
    float fCardMatchTh; 
    float fCardDeformationTh;
    float fMetalTagReflectionTh;
    float fMetalTagReflectionDensityTh;
    DEFAULT_COMPARISON(AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_PARAMS);
} AuthMeIDCardAntiFraudParams;

typedef struct AUTHME_IMAGE_REFLECTIVE_INFO
{
    float fScore;
    DEFAULT_COMPARISON(AUTHME_IMAGE_REFLECTIVE_INFO);
} AuthMeImageReflectiveInfo;

typedef struct AUTHME_IMAGE_BLUR_INFO
{
    float fScore;
    DEFAULT_COMPARISON(AUTHME_IMAGE_BLUR_INFO);
} AuthMeImageBlurInfo;

typedef struct AUTHME_IMAGE_THICKNESS_INFO
{
    float fScore;
    DEFAULT_COMPARISON(AUTHME_IMAGE_THICKNESS_INFO)
} AuthMeImageThicknessInfo;

typedef struct AUTHME_ID_CARD_COLOR_INFO
{
    float fScore;
    DEFAULT_COMPARISON(AUTHME_ID_CARD_COLOR_INFO)
} AuthMeIDCardColorInfo;

typedef struct AUTHME_BARCODE_INFO
{
    char fBarcode_1[20];
    char fBarcode_2[20];
    DEFAULT_COMPARISON(AUTHME_BARCODE_INFO)
} AuthMeBarcodeInfo;

typedef struct AUTHME_METAL_TAL_INFO
{
    EAuthMeIDCardMetalTagStatus aeStatus[3];
    int aiPosition[3][4];
    bool hasAntiFeature;
    DEFAULT_COMPARISON(AUTHME_METAL_TAL_INFO)
} AuthMeMetalTagInfo;

typedef struct AUTHME_CARD_CLASS_ATTRIBUTE
{
    char country[10];
    char document[50];
    char fragment[20];
    char variance[100];
    DEFAULT_COMPARISON(AUTHME_CARD_CLASS_ATTRIBUTE)
} AuthMeCardClassAttribute;

typedef struct AUTHME_CARD_CLASS_INFO
{
    EAuthMeCardClass eClass; //'eClass' is deprecated.
    char cardType[100];
    AuthMeCardClassAttribute attribute;
    DEFAULT_COMPARISON(AUTHME_CARD_CLASS_INFO)
} AuthMeCardClassInfo;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_INFO
{
    int aiCardVertices[8];
    int aiCardMatchVertices[8];
    int iFrameIndex;
    float fCardMatchScore;
    float fCardDeformation;
    bool isCardInsideROI;
    bool isCardCutByCamera;
    EAuthMeCardMatchStatus eCardMatchStatus;
    AuthMeImageReflectiveInfo reflective;
    AuthMeImageBlurInfo blur;
    AuthMeImageThicknessInfo thickness;
    AuthMeIDCardColorInfo colorDetect;
    AuthMeMetalTagInfo metalTag;
    AuthMeImageReflectiveInfo metalTagReflection;
    AuthMeCardClassInfo cardClass;
    DEFAULT_COMPARISON(AUTHME_ID_CARD_ANTI_FRAUD_INFO)
} AuthMeIDCardAntiFraudInfo;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_STATISTICS
{
    int iValidMetalTagCount;
    DEFAULT_COMPARISON(AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_STATISTICS)
} AuthMeIDCardAntiFraudStatistics;


#define ID_CARD_ANTI_FRAUD_SERVICE_STAGE_TAG(decorate) \
    decorate(Frontal) \
    decorate(Up) \
    decorate(Down) \
    decorate(Left) \
    decorate(Right) \
    decorate(IgnoreCardMatch) \
    decorate(Done)
//
//#define ID_CARD_ANTI_FRAUD_SERVICE_STAGE_PREFIX(name) eAuthMe_IDCardFraudService_Stage_##name,
typedef enum E_AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_STATGE
{
    eAuthMe_IDCardFraudService_Stage_Frontal,
    eAuthMe_IDCardFraudService_Stage_Up,
    eAuthMe_IDCardFraudService_Stage_Down,
    eAuthMe_IDCardFraudService_Stage_Left,
    eAuthMe_IDCardFraudService_Stage_Right,
    eAuthMe_IDCardFraudService_Stage_IgnoreCardMatch,
    eAuthMe_IDCardFraudService_Stage_Done,
} EAuthMeIDCardAntiFraudStage;


#define ID_CARD_ANTI_FRAUD_SERVICE_STATUS_TAG(decorate) \
    decorate(Pass) \
    decorate(Failed) \
    decorate(NoCard) \
    decorate(WrongCardType) \
    decorate(CardCutByCamera) \
    decorate(CardThicknessFailed) \
    decorate(Reflective) \
    decorate(Blur) \
    decorate(CardNotInROI) \
    decorate(CardTooSmall) \
    decorate(NeedDeformationFrontal) \
    decorate(NeedDeformationLeft) \
    decorate(NeedDeformationRight) \
    decorate(NeedDeformationUp) \
    decorate(NeedDeformationDown) \
    decorate(NeedHoldCard) \
    decorate(StagePass) \
    decorate(NeedMoreFrame) \
    decorate(Undefined) \
    decorate(Error)  \
    /* deprecated */ \
    decorate(Gray) \
    decorate(AntiFraudFeatureDetect) \
    decorate(PositionNotMatch)
//
//#define ID_CARD_ANTI_FRAUD_SERVICE_STATUS_PREFIX(name) eAuthMe_IDCardFraudService_##name,
typedef enum E_AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_STATUS
{
    eAuthMe_IDCardFraudService_Pass,
    eAuthMe_IDCardFraudService_Failed,
    eAuthMe_IDCardFraudService_NoCard,
    eAuthMe_IDCardFraudService_WrongCardType,
    eAuthMe_IDCardFraudService_CardCutByCamera,
    eAuthMe_IDCardFraudService_CardThicknessFailed,
    eAuthMe_IDCardFraudService_Reflective,
    eAuthMe_IDCardFraudService_Blur,
    eAuthMe_IDCardFraudService_CardNotInROI,
    eAuthMe_IDCardFraudService_CardTooSmall,
    eAuthMe_IDCardFraudService_NeedDeformationFrontal,
    eAuthMe_IDCardFraudService_NeedDeformationLeft,
    eAuthMe_IDCardFraudService_NeedDeformationRight,
    eAuthMe_IDCardFraudService_NeedDeformationUp,
    eAuthMe_IDCardFraudService_NeedDeformationDown,
    eAuthMe_IDCardFraudService_NeedHoldCard,
    eAuthMe_IDCardFraudService_StagePass,
    eAuthMe_IDCardFraudService_NeedMoreFrame,
    eAuthMe_IDCardFraudService_Undefined,
    eAuthMe_IDCardFraudService_Error,
    eAuthMe_IDCardFraudService_Gray,
    eAuthMe_IDCardFraudService_AntiFraudFeatureDetect,
    eAuthMe_IDCardFraudService_PositionNotMatch,
} EAuthMeIDCardAntiFraudStatus;


typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_RESULT
{
    int iIsKeyFrame;
    AuthMeIDCardAntiFraudInfo info;
    AuthMeIDCardAntiFraudStatistics statistics;
    EAuthMeIDCardAntiFraudStage eStage;
    EAuthMeIDCardAntiFraudStatus eStatus;
    DEFAULT_COMPARISON(AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_RESULT)
} AuthMeIDCardAntiFraudResult;

typedef struct AUTHME_CARD_OCR_MODELS
{
    long OCR_00;
    long OCR_01;
    long OCR_01_FB;
    long OCR_03;
} AuthMeCardOCRModels;


#define CARD_OCR_SERVICE_PARAMS_CONTENT(decorate) \
    /* algo params */ \
    decorate(float, fCardClassificationTh) \
    decorate(float, fImageReflectiveMaskTh) \
    decorate(float, fImageReflectiveTriggerTh) \
    decorate(float, fIDCardColorTh) \
    decorate(float, fImageBlurTh) \
    /* other params */ \
    decorate(float, fCardMatchTh)

typedef struct AUTHME_CARD_OCR_PARAMS
{
    CARD_OCR_SERVICE_PARAMS_CONTENT(IMPL_VAR)
    DEFAULT_COMPARISON(AUTHME_CARD_OCR_PARAMS)
} AuthMeCardOCRParams;


#define CARD_OCR_SERVICE_STATUS_TAG(decorate) \
    decorate(NoCard) \
    decorate(WrongCardType) \
    decorate(PositionNotMatch) \
    decorate(Reflective) \
    decorate(Gray) \
    decorate(Blur) \
    decorate(Pass) \
    decorate(Error)

//#define CARD_OCR_SERVICE_STATUS_PREFIX(name) eAuthMe_CardOCR_##name,
typedef enum E_AUTHME_CARD_OCR_STATUS
{
    eAuthMe_CardOCR_NoCard,
    eAuthMe_CardOCR_WrongCardType,
    eAuthMe_CardOCR_PositionNotMatch,
    eAuthMe_CardOCR_Reflective,
    eAuthMe_CardOCR_Gray,
    eAuthMe_CardOCR_Blur,
    eAuthMe_CardOCR_Pass,
    eAuthMe_CardOCR_Error,
} EAuthMeCardOCRStatus;

typedef struct AUTHME_CARD_OCR_INFO
{
    int aiCardVertices[8];
    int aiCardMatchVertices[8];
    float fCardMatchScore;
    AuthMeCardClassInfo cardClass;
    AuthMeImageReflectiveInfo reflective;
    AuthMeIDCardColorInfo colorDetect;
    AuthMeImageBlurInfo blur;
    AuthMeBarcodeInfo barcode;
    DEFAULT_COMPARISON(AUTHME_CARD_OCR_INFO)
} AuthMeCardOCRInfo;

typedef struct AUTHME_CARD_OCR_RESULT
{
    AuthMeCardOCRInfo info;
    EAuthMeCardOCRStatus eStatus;
    AuthMeImage image;
    DEFAULT_COMPARISON(AUTHME_CARD_OCR_RESULT)
} AuthMeCardOCRResult;

typedef struct AUTHME_MRZ_SERVICE_MODELS
{
    long OCR_00;
    long OCR_01;
    long OCR_01_FB;
    long OCR_03;
    long MRZ_00;
    long MRZ_01;
} AuthMeMRZServiceModels;

typedef struct AUTHME_MRZ_SERVICE_INFO
{
    float fPositionMatchScore;
    int aiCardVertices[8];
    int aiMRZVertices[2][8];
    AuthMeCardClassInfo cardClass;
    AuthMeImageReflectiveInfo reflective;
    AuthMeImageBlurInfo blur;
    EAuthMeMRZRecogStatus eRecogStatus;
    DEFAULT_COMPARISON(AUTHME_MRZ_SERVICE_INFO)
} AuthMeMRZServiceInfo;

#define MRZ_SERVICE_PARAMS_CONTENT(decorate) \
    decorate(float, fImageReflectiveMaskTh) \
    decorate(float, fImageReflectiveTriggerTh) \
    decorate(float, fImageBlurTh) \
    decorate(float, fPositionMatchTh)\
    decorate(float, fCardClassificationTh)

typedef struct AUTHME_MRZ_SERVICE_PARAMS
{
    float fImageReflectiveMaskTh;
    float fImageReflectiveTriggerTh;
    float fImageBlurTh;
    float fPositionMatchTh;
    float fCardClassificationTh;
    DEFAULT_COMPARISON(AUTHME_MRZ_SERVICE_PARAMS)
} AuthMeMRZServiceParams;

#define MRZ_SERVICE_STATUS_TAG(decorate) \
    decorate(NotFound) \
    decorate(NotAligned) \
    decorate(Reflective) \
    decorate(Blur) \
    decorate(WrongCardType) \
    decorate(MRZNotFound) \
    decorate(RecogFailed) \
    decorate(Success) \
    decorate(Error)

#define MRZ_SERVICE_STATUS_PREFIX(name) eAuthMe_MRZService_##name,
typedef enum E_AUTHME_MRZ_SERVICE_STATUS
{
    eAuthMe_MRZService_NotFound,
    eAuthMe_MRZService_NotAligned,
    eAuthMe_MRZService_Reflective,
    eAuthMe_MRZService_Blur,
    eAuthMe_MRZService_WrongCardType,
    eAuthMe_MRZService_MRZNotFound,
    eAuthMe_MRZService_RecogFailed,
    eAuthMe_MRZService_Success,
    eAuthMe_MRZService_Error,
} EAuthMeMRZServiceStatus;

typedef struct AUTHME_MRZ_SERVICE_RESULT
{
    AuthMeMRZServiceInfo info;
    EAuthMeMRZServiceStatus eStatus;
    AuthMeMRZField tField;
    AuthMeImage image;
} AuthMeMRZServiceResult;

typedef enum _E_AUTHME_MRZ_TYPE
{
    eAuthMe_MRZ_TD1,
    eAuthMe_MRZ_TD3
} EAuthMeMRZType;

#ifdef __cplusplus
}
#endif
