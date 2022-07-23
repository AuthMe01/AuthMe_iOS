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

typedef struct AUTHME_FAS_PARAMS
{
    // algo params
    float fFaceDetectTh;
    float fMaskTh;
    float fEyeTh;
    float fMouthTh;
    float fFASTh;
    float fMiniFASTh;
    int iFASAccumulativeNum;
    // other params
    int timeoutSec;
    int fasTimeoutSec;
    float fFaceRoiPreviewRatioW;
    float fFaceRoiAspectRatioH;
    AuthMePointFloat faceRoiShift; // x, y in range [0~1]
    float fNotAtCenterTh;
    float fFaceTooSmallTh;
    float fFaceTooLargeTh;
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
    eAuthMe_FASService_NeedMoreFrame,
    eAuthMe_FASService_Pass,
    eAuthMe_FASService_Error,
} EAuthMeFASServiceStatus;

const int FAS_SERVICE_STAGE_START_LINE = __LINE__;
typedef enum E_AUTHME_FAS_SERVICE_STAGE
{
    eAuthMe_FASService_Stage_Passive,
    eAuthMe_FASService_Stage_OpenMouth,
    eAuthMe_FASService_Stage_CloseMouth,
    eAuthMe_FASService_Stage_Smile,
    eAuthMe_FASService_Stage_Done,
} EAuthMeFASServiceStage;
const int iAuthMeFASServiceStageCount = __LINE__ - FAS_SERVICE_STAGE_START_LINE - 4;


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

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_PARAMS
{
    // algo params
    float fCardClassificationTh;
    float fLaserTagDetectionTh;
    float fTaiwanHoleDetectionTh;
    float fMetalTagDetectionTh;
    float fImageReflectiveTh;
    float fImageBlurTh;
    float fIDCardColorTh;
    // other params
    int timeoutSec;
    int iHasLaserTagCountTh;
    int iNoLaserTagCountTh;
    int iTaiwanHoleCountTh;
    int iMetalTagValidCountTh;
    int iCardMatchFrameNum;
    float fCardMatchTh;
    float fMetalTagReflectionTh;
    float fMetalTagReflectionDensityTh;
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

typedef enum E_AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_STATUS
{
    eAuthMe_IDCardFraudService_Failed,
    eAuthMe_IDCardFraudService_NoCard,
    eAuthMe_IDCardFraudService_WrongCardType,
    eAuthMe_IDCardFraudService_Reflective,
    eAuthMe_IDCardFraudService_Blur,
    eAuthMe_IDCardFraudService_Gray,
    eAuthMe_IDCardFraudService_NeedMoreFrame,
    eAuthMe_IDCardFraudService_Pass,
    eAuthMe_IDCardFraudService_Error,
} EAuthMeIDCardAntiFraudStatus;

typedef enum E_AUTHME_CARD_MTACH_STATUS
{
    eAuthMe_CardMatch_None,
    eAuthMe_CardMatch_Mismatch,
    eAuthMe_CardMatch_NeedMoreFrame,
    eAuthMe_CardMatch_Match,
} EAuthMeCardMatchStatus;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_RESULT
{
    AuthMeIDCardAntiFraudInfo info;
    AuthMeIDCardAntiFraudStatistics statistics;
    EAuthMeIDCardAntiFraudStatus eAntiFraudStatus;
    EAuthMeCardMatchStatus eCardMatchStatus;
} AuthMeIDCardAntiFraudResult;

typedef struct AUTHME_CARD_OCR_MODELS
{
    long cardDetectionModel;
    long cardClassificationModel;
    long reflectionDetectionModel;
} AuthMeCardOCRModels;

typedef struct AUTHME_CARD_OCR_PARAMS
{
    // algo params
    float fCardClassificationTh;
    float fImageReflectiveMaskTh;
    float fImageReflectiveTriggerTh;
    float fImageBlurTh;
    // other params
    float fCardMatchTh;
    EAuthMeCardClass eTargetCardType;
    AuthMeSize outputSize;
    DEFAULT_COMPARISON(AUTHME_CARD_OCR_PARAMS)
} AuthMeCardOCRParams;

typedef enum E_AUTHME_CARD_OCR_STATUS
{
    eAuthMe_CardOCR_NoCard,
    eAuthMe_CardOCR_WrongCardType,
    eAuthMe_CardOCR_PositionNotMatch,
    eAuthMe_CardOCR_Reflective,
    eAuthMe_CardOCR_Blur,
    eAuthMe_CardOCR_Pass,
    eAuthMe_CardOCR_Error,
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
    float fScore;
    float Points[8];
    DEFAULT_COMPARISON(AUTHME_MRZ_INFO)
} AuthMeMRZInfo;

typedef struct AUTHME_MRZ_PARAMS
{
    int dummy;
    DEFAULT_COMPARISON(AUTHME_MRZ_PARAMS)
} AuthMeMRZParams;

typedef struct AUTHME_MRZ_RESULT
{
    AuthMeMRZInfo info;
    EAuthMeMRZRecogStatus eStatus;
    AuthMeMRZFieldTD3 tField;
} AuthMeMRZResult;


#ifdef __cplusplus
}
#endif
