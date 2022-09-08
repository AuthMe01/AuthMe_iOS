#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_type.h"
#include "engine_base.h"

// c an c++ shared structures and types

typedef enum
{
    eAuthMe_SDKAuth_JsonFormatError,
    eAuthMe_SDKAuth_MissingServiceCrtKey,
    eAuthMe_SDKAuth_MissingDataKey,
    eAuthMe_SDKAuth_MissingSignatureKey,
    eAuthMe_SDKAuth_X509CrtVerifyFail,
    eAuthMe_SDKAuth_SignVerifyFail,
    eAuthMe_SDKAuth_Pass,
} EAuthMeSDKAuthStatus;

typedef struct AUTHME_MODEL_VERSION
{
    char szName[32];
    char szVersion[8];
} AuthMeModelVersion;


#define CARD_MATCH_STATUS_TAG(decorate) \
    decorate(None) \
    decorate(Mismatch) \
    decorate(NeedMoreFrame) \
    decorate(Match)

#define CARD_MATCH_STATUS_PREFIX(name) eAuthMe_CardMatch_##name,
typedef enum E_AUTHME_CARD_MTACH_STATUS
{
    CARD_MATCH_STATUS_TAG(CARD_MATCH_STATUS_PREFIX)
} EAuthMeCardMatchStatus;


typedef struct AUTHME_FAS_SERVICE_MODELS
{
    long faceDetectModel;
    long faceAlignmentModel;
    long fasModel;
    long miniFASModel;
} AuthMeFASServiceModels;

typedef struct AUTHME_FAS_SERVICE_UI_PARAMS
{
    AuthMeSize analyzeSize; // pixel
    AuthMeRectFloat previewPosition; // l, t, r, b in range [0~1]
    DEFAULT_COMPARISON(AUTHME_FAS_SERVICE_UI_PARAMS)
} AuthMeV3ServiceUIParams;

typedef struct AUTHME_EYE_INFO
{
    EAuthMeEyeStatus eStatus;
    float fScore;
    DEFAULT_COMPARISON(AUTHME_EYE_INFO)
} AuthMeEyeInfo;

typedef struct AUTHME_MOUTH_INFO
{
    EAuthMeMouthStatus eStatus;
    float fScore;
    DEFAULT_COMPARISON(AUTHME_MOUTH_INFO)
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
    DEFAULT_COMPARISON(AUTHME_MINI_FAS_INFO)
} AuthMeMiniFASInfo;

typedef struct AUTHME_FAS_INFO
{
    EAuthMeFaceAntiSpoofingStatus eStatus;
    float fScore;
    DEFAULT_COMPARISON(AUTHME_FAS_INFO)
} AuthMeFASInfo;

typedef struct AUTHME_FAS_STAGE_PARAMS
{
    int applyFAS;
    int iFrameNum;
    float fThreshold;
    DEFAULT_COMPARISON(AUTHME_FAS_STAGE_PARAMS)
} AuthMeFASStageParams;

#define IMPL_VAR(type, name) type name;

#define FAS_SERVICE_PARAMS_CONTENT(decorate) \
    /* algo params */ \
    decorate(float, fFaceDetectTh) \
    decorate(float, fMaskTh) \
    decorate(float, fEyeTh) \
    decorate(float, fMouthTh) \
    decorate(float, fFASTh) \
    decorate(float, fMiniFASTh) \
    decorate(int, iFASAccumulativeNum) \
    /* other params */ \
    decorate(int, timeoutSec) \
    decorate(int, fasTimeoutSec) \
    decorate(float, fFaceRoiPreviewRatioW) \
    decorate(float, fFaceRoiAspectRatioH) \
    decorate(AuthMePointFloat, faceRoiShift) \
    decorate(float, fNotAtCenterTh) \
    decorate(float, fFaceTooSmallTh) \
    decorate(float, fFaceTooLargeTh)

typedef struct AUTHME_FAS_PARAMS
{
    FAS_SERVICE_PARAMS_CONTENT(IMPL_VAR)
    DEFAULT_COMPARISON(AUTHME_FAS_PARAMS)
} AuthMeFASParams;

typedef struct AUTHME_FAS_SERVICE_INFO
{
    AuthMeFaceInfo face;
    AuthMeEyeInfo eye;
    AuthMeMouthInfo mouth;
    AuthMeFacePoseInfo pose;
    AuthMeMiniFASInfo miniFAS;
    AuthMeFASInfo fas;
    DEFAULT_COMPARISON(AUTHME_FAS_SERVICE_INFO)
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
    decorate(NeedMoreFrame) \
    decorate(Pass) \
    decorate(Error)

#define FAS_SERVICE_STATUS_PREFIX(name) eAuthMe_FASService_##name,
typedef enum E_AUTHME_FAS_SERVICE_STATUS
{
    FAS_SERVICE_STATUS_TAG(FAS_SERVICE_STATUS_PREFIX)
} EAuthMeFASServiceStatus;


const int FAS_SERVICE_STAGE_START_LINE = __LINE__;
#define FAS_SERVICE_STAGE_TAG(decorate) \
    decorate(Passive) \
    decorate(OpenMouth) \
    decorate(CloseMouth) \
    decorate(Smile) \
    decorate(Done)
const int iAuthMeFASServiceStageCount = __LINE__ - FAS_SERVICE_STAGE_START_LINE - 2;

#define FAS_SERVICE_STAGE_PREFIX(name) eAuthMe_FASService_Stage_##name,
typedef enum E_AUTHME_FAS_SERVICE_STAGE
{
    FAS_SERVICE_STAGE_TAG(FAS_SERVICE_STAGE_PREFIX)
} EAuthMeFASServiceStage;

typedef struct AUTHME_FAS_RESULT
{
    float fStageScore;
    AuthMeFASServiceInfo info;
    EAuthMeFASServiceStatus eStatus;
    EAuthMeFASServiceStage eStage;
    DEFAULT_COMPARISON(AUTHME_FAS_RESULT)
} AuthMeFASResult;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_MODELS
{
    long cardDetectionModel;
    long cardClassificationModel;
    long laserTagDetectionModel;
    long taiwanHoleDetectionModel;
    long metalTagDetectionModel;
    long reflectionDetectionModel;
} AuthMeIDCardAntiFraudServiceModels;

#define ID_CARD_ANTI_FRAUD_SERVICE_PARAMS_CONTENT(decorate) \
    /* algo params */ \
    decorate(float, fCardClassificationTh) \
    decorate(float, fLaserTagDetectionTh) \
    decorate(float, fTaiwanHoleDetectionTh) \
    decorate(float, fMetalTagDetectionTh) \
    decorate(float, fImageReflectiveTh) \
    decorate(float, fImageBlurTh) \
    decorate(float, fIDCardColorTh) \
    /* other params */ \
    decorate(int, timeoutSec) \
    decorate(int, iHasLaserTagCountTh) \
    decorate(int, iNoLaserTagCountTh) \
    decorate(int, iTaiwanHoleCountTh) \
    decorate(int, iMetalTagValidCountTh) \
    decorate(int, iCardMatchFrameNum) \
    decorate(float, fCardMatchTh) \
    decorate(float, fMetalTagReflectionTh) \
    decorate(float, fMetalTagReflectionDensityTh)

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_PARAMS
{
    ID_CARD_ANTI_FRAUD_SERVICE_PARAMS_CONTENT(IMPL_VAR)
    DEFAULT_COMPARISON(AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_PARAMS)
} AuthMeIDCardAntiFraudParams;

typedef struct AUTHME_IMAGE_REFLECTIVE_INFO
{
    float fScore;
    DEFAULT_COMPARISON(AUTHME_IMAGE_REFLECTIVE_INFO)
} AuthMeImageReflectiveInfo;

typedef struct AUTHME_IMAGE_BLUR_INFO
{
    float fScore;
    DEFAULT_COMPARISON(AUTHME_IMAGE_BLUR_INFO)
} AuthMeImageBlurInfo;

typedef struct AUTHME_ID_CARD_COLOR_INFO
{
    float fScore;
} AuthMeIDCardColorInfo;

typedef struct AUTHME_METAL_TAL_INFO
{
    EAuthMeIDCardMetalTagStatus aeStatus[3];
    int aiPosition[3][4];
} AuthMeMetalTagInfo;

typedef struct AUTHME_LASER_TAL_INFO
{
    EAuthMeLaserTagStatus eStatus;
} AuthMeLaserTagInfo;

typedef struct AUTHME_TAIWAN_HOLE_INFO
{
    EAuthMeTaiwanHoleStatus eStatus;
} AuthMeTaiwanHoleInfo;

typedef struct AUTHME_CARD_CLASS_INFO
{
    EAuthMeCardClass eClass;
    DEFAULT_COMPARISON(AUTHME_CARD_CLASS_INFO)
} AuthMeCardClassInfo;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_INFO
{
    int aiCardVertices[8];
    float fCardMatchScore;
    EAuthMeCardMatchStatus eCardMatchStatus;
    AuthMeImageReflectiveInfo reflective;
    AuthMeImageBlurInfo blur;
    AuthMeIDCardColorInfo colorDetect;
    AuthMeMetalTagInfo metalTag;
    AuthMeImageReflectiveInfo metalTagReflection;
    AuthMeLaserTagInfo laserTag;
    AuthMeTaiwanHoleInfo taiwanHole;
    AuthMeCardClassInfo cardClass;
} AuthMeIDCardAntiFraudInfo;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_STATISTICS
{
    int iHasLaserTagCount;
    int iNoLaserTagCount;
    int iTaiwanHoleCount;
    int iValidMetalTagCount;
} AuthMeIDCardAntiFraudStatistics;


#define ID_CARD_ANTI_FRAUD_SERVICE_STAGE_TAG(decorate) \
    decorate(Frontal) \
    decorate(Up) \
    decorate(Down) \
    decorate(Left) \
    decorate(Right) \
    decorate(IgnoreCardMatch) \
    decorate(Done)

#define ID_CARD_ANTI_FRAUD_SERVICE_STAGE_PREFIX(name) eAuthMe_IDCardFraudService_Stage_##name,
typedef enum E_AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_STATGE
{
    ID_CARD_ANTI_FRAUD_SERVICE_STAGE_TAG(ID_CARD_ANTI_FRAUD_SERVICE_STAGE_PREFIX)
} EAuthMeIDCardAntiFraudStage;


#define ID_CARD_ANTI_FRAUD_SERVICE_STATUS_TAG(decorate) \
    decorate(Failed) \
    decorate(NoCard) \
    decorate(WrongCardType) \
    decorate(Reflective) \
    decorate(Blur) \
    decorate(Gray) \
    decorate(PositionNotMatch) \
    decorate(NeedMoreFrame) \
    decorate(Pass) \
    decorate(Error)

#define ID_CARD_ANTI_FRAUD_SERVICE_STATUS_PREFIX(name) eAuthMe_IDCardFraudService_##name,
typedef enum E_AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_STATUS
{
    ID_CARD_ANTI_FRAUD_SERVICE_STATUS_TAG(ID_CARD_ANTI_FRAUD_SERVICE_STATUS_PREFIX)
} EAuthMeIDCardAntiFraudStatus;


typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_RESULT
{
    AuthMeIDCardAntiFraudInfo info;
    AuthMeIDCardAntiFraudStatistics statistics;
    EAuthMeIDCardAntiFraudStage eStage;
    EAuthMeIDCardAntiFraudStatus eStatus;
} AuthMeIDCardAntiFraudResult;

typedef struct AUTHME_CARD_OCR_MODELS
{
    long cardDetectionModel;
    long cardClassificationModel;
    long reflectionDetectionModel;
} AuthMeCardOCRModels;


#define CARD_OCR_SERVICE_PARAMS_CONTENT(decorate) \
    /* algo params */ \
    decorate(float, fCardClassificationTh) \
    decorate(float, fImageReflectiveMaskTh) \
    decorate(float, fImageReflectiveTriggerTh) \
    decorate(float, fImageBlurTh) \
    /* other params */ \
    decorate(float, fCardMatchTh) \
    decorate(EAuthMeCardClass, eTargetCardType) \
    decorate(AuthMeSize, outputSize)

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
    decorate(Blur) \
    decorate(Pass) \
    decorate(Error)

#define CARD_OCR_SERVICE_STATUS_PREFIX(name) eAuthMe_CardOCR_##name,
typedef enum E_AUTHME_CARD_OCR_STATUS
{
    CARD_OCR_SERVICE_STATUS_TAG(CARD_OCR_SERVICE_STATUS_PREFIX)
} EAuthMeCardOCRStatus;

typedef struct AUTHME_CARD_OCR_INFO
{
    int aiCardVertices[8];
    float fCardMatchScore;
    AuthMeCardClassInfo cardClass;
    AuthMeImageReflectiveInfo reflective;
    AuthMeImageBlurInfo blur;
    DEFAULT_COMPARISON(AUTHME_CARD_OCR_INFO)
} AuthMeCardOCRInfo;

typedef struct AUTHME_CARD_OCR_RESULT
{
    AuthMeCardOCRInfo info;
    EAuthMeCardOCRStatus eStatus;
    AuthMeImage image;
    DEFAULT_COMPARISON(AUTHME_CARD_OCR_RESULT)
} AuthMeCardOCRResult;

typedef struct AUTHME_MRZ_MODELS
{
    long mrzDetectionModel;
    long mrzRecognitionModel;
} AuthMeMRZModels;

typedef struct AUTHME_MRZ_INFO
{
    float afVertices[8];
    EAuthMeMRZRecogStatus eRecogStatus;
    DEFAULT_COMPARISON(AUTHME_MRZ_INFO)
} AuthMeMRZInfo;

#define MRZ_SERVICE_PARAMS_CONTENT(decorate) \
    decorate(int, dummy)

typedef struct AUTHME_MRZ_SERVICE_PARAMS
{
    MRZ_SERVICE_PARAMS_CONTENT(IMPL_VAR)
    DEFAULT_COMPARISON(AUTHME_MRZ_SERVICE_PARAMS)
} AuthMeMRZParams;

#define MRZ_SERVICE_STATUS_TAG(decorate) \
    decorate(NotFound) \
    decorate(RecogFailed) \
    decorate(Success) \
    decorate(Error)

#define MRZ_SERVICE_STATUS_PREFIX(name) eAuthMe_MRZService_##name,
typedef enum E_AUTHME_MRZ_SERVICE_STATUS
{
    MRZ_SERVICE_STATUS_TAG(MRZ_SERVICE_STATUS_PREFIX)
} EAuthMeMRZServiceStatus;

typedef struct AUTHME_MRZ_RESULT
{
    AuthMeMRZInfo info;
    EAuthMeMRZServiceStatus eStatus;
    AuthMeMRZFieldTD3 tField;
} AuthMeMRZResult;


#ifdef __cplusplus
}
#endif
