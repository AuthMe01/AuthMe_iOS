#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine_type.h"
#include "engine_base.h"

// c an c++ shared structures and types

typedef struct AUTHME_BUFFER_INFO
{
    const void* pData;
    int iSize;
} AuthMeBufferInfo;

typedef struct AUTHME_MODEL_INIT_INFO
{
    // set szPath or buffer
    const char* szPath;
    AuthMeBufferInfo buffer;
} AuthMeModelInitInfo;

typedef struct AUTHME_MODEL_VERSION
{
    char szName[32];
    char szVersion[8];
} AuthMeModelVersion;

typedef struct AUTHME_FAS_SERVICE_MODELS
{
    AuthMeModelInitInfo faceDetectModel;
    AuthMeModelInitInfo faceAlignmentModel;
    AuthMeModelInitInfo fasModel;
} AuthMeFASServiceModels;

typedef struct AUTHME_FAS_SERVICE_UI_PARAMS
{
    AuthMeSize analyzeSize; // pixel
    AuthMeRectFloat previewPosition; // l, t, r, b in range [0~1]
} AuthMeV3ServiceUIParams;

typedef struct AUTHME_EYE_INFO
{
    EAuthMeEyeStatus eStatus;
    float fScore;
} AuthMeEyeInfo;

typedef struct AUTHME_MOUTH_INFO
{
    EAuthMeMouthStatus eStatus;
    float fScore;
} AuthMeMouthInfo;

typedef struct AUTHME_FACE_POSE_INFO
{
    EAuthMeFacePose ePose;
} AuthMeFacePoseInfo;

typedef struct AUTHME_FAS_INFO
{
    EAuthMeFaceAntiSpoofingStatus eStatus;
    float fScore;
} AuthMeFASInfo;

typedef struct AUTHME_FAS_PARAMS
{
    // algo params
    float fFaceDetectTh;
    float fMaskTh;
    float fEyeTh;
    float fMouthTh;
    float fFASTh;
    int iFASAccumulativeNum;
    // other params
    int timeoutSec;
    float fFaceRoiPreviewRatioW;
    float fFaceRoiAspectRatioH;
    AuthMePointFloat faceRoiShift; // x, y in range [0~1]
    float fNotAtCenterTh;
    float fFaceTooSmallTh;
    float fFaceTooLargeTh;
} AuthMeFASParams;

typedef struct AUTHME_FAS_SERVICE_INFO
{
    AuthMeFaceInfo face;
    AuthMeEyeInfo eye;
    AuthMeMouthInfo mouth;
    AuthMeFacePoseInfo pose;
    AuthMeFASInfo fas;
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
    eAuthMe_FASService_Stage_Done,
} EAuthMeFASServiceStage;
const int iAuthMeFASServiceStageCount = __LINE__ - FAS_SERVICE_STAGE_START_LINE - 4;

typedef struct AUTHME_FAS_RESULT
{
    AuthMeFASServiceInfo info;
    EAuthMeFASServiceStatus eStatus;
    EAuthMeFASServiceStage eStage;
} AuthMeFASResult;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_SERVICE_MODELS
{
    AuthMeModelInitInfo cardDetectionModel;
    AuthMeModelInitInfo cardClassificationModel;
    AuthMeModelInitInfo laserTagDetectionModel;
    AuthMeModelInitInfo taiwanHoleDetectionModel;
    AuthMeModelInitInfo metalTagDetectionModel;
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
} AuthMeIDCardAntiFraudParams;

typedef struct AUTHME_IMAGE_REFLECTIVE_INFO
{
    float fScore;
} AuthMeImageReflectiveInfo;

typedef struct AUTHME_IMAGE_BLUR_INFO
{
    float fScore;
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
} AuthMeCardClassInfo;

typedef struct AUTHME_ID_CARD_ANTI_FRAUD_INFO
{
    int aiCardVertices[8];
    float fCardMatchScore;
    AuthMeImageReflectiveInfo reflective;
    AuthMeImageBlurInfo blur;
    AuthMeIDCardColorInfo colorDetect;
    AuthMeMetalTagInfo metalTag;
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
    AuthMeModelInitInfo cardDetectionModel;
    AuthMeModelInitInfo cardClassificationModel;
    AuthMeModelInitInfo reflectionDetectionModel;
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
} AuthMeCardOCRInfo;

typedef struct AUTHME_CARD_OCR_RESULT
{
    AuthMeCardOCRInfo info;
    EAuthMeCardOCRStatus eStatus;
    AuthMeImage image;
} AuthMeCardOCRResult;

#ifdef __cplusplus
}
#endif
