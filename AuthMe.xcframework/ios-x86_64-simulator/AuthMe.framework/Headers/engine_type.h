#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _E_AUTHME_COLOR_FORMAT
{
    eAuthMe_ColorFormat_RGBA_8888 = 1,
    eAuthMe_ColorFormat_BGR,
    eAuthMe_ColorFormat_RGB,
} EAuthMeColorFormat;

typedef enum _E_AUTHME_FACE_ANTI_SPOOFING_STATUS
{
    eAuthMe_FaceAntiSpoofing_FrameNotEnough,
    eAuthMe_FaceAntiSpoofing_Real,
    eAuthMe_FaceAntiSpoofing_Spoof,
} EAuthMeFaceAntiSpoofingStatus;

typedef enum _E_AUTHME_FACE_POSE : int
{
    eAuthMe_FacePose_Unknown = -1,
    eAuthMe_FacePose_LeftProfile = 0,
    eAuthMe_FacePose_LeftFrontal,
    eAuthMe_FacePose_Frontal,
    eAuthMe_FacePose_RightFrontal,
    eAuthMe_FacePose_RightProfile,
    eAuthMe_FacePose_UpFrontal,
    eAuthMe_FacePose_DownFrontal,
} EAuthMeFacePose;

typedef enum _E_AUTHME_CARD_CLASS : int
{
    eAuthMe_Card_Invalid = -1,
    eAuthMe_Card_Background = 0,
    eAuthMe_Card_Unknown,
    eAuthMe_Card_Passport,
    eAuthMe_Card_TWN_IDCard_Front,
    eAuthMe_Card_TWN_IDCard_Back,
    eAuthMe_Card_TWN_DriverLicense_Front,
    eAuthMe_Card_TWN_DriverLicense_Back,
    eAuthMe_Card_TWN_Resident_Front,
    eAuthMe_Card_TWN_Resident_Back,
    eAuthMe_Card_TWN_Health_Front,
    eAuthMe_Card_TWN_VehiclesLicense_Front,
} EAuthMeCardClass;

typedef enum _E_AUTHME_LASER_TAG_STATUS : int
{
    eAuthMe_LaserTag_NoTag = 0,
    eAuthMe_LaserTag_HasTag,
    eAuthMe_LaserTag_Others,
} EAuthMeLaserTagStatus;

typedef enum E_AUTHME_TWIWAN_HOLE_STATUS : int
{
    eAuthMe_TaiwanHole_NotFound = 0,
    eAuthMe_TaiwanHole_Found,
} EAuthMeTaiwanHoleStatus;

typedef enum _E_AUTHME_MRZ_RECOG_STATUS : int
{
    eAuthMe_MRZ_Success = 0,
    eAuthMe_MRZ_WrongFormat,
} EAuthMeMRZRecogStatus;

typedef enum _AUTHME_EYE_STATUS : int
{
    eAuthMe_Eye_Close = 0,
    eAuthMe_Eye_Open,
} EAuthMeEyeStatus;

typedef enum _AUTHME_MOUTH_STATUS : int
{
    eAuthMe_Mouth_Close = 0,
    eAuthMe_Mouth_Open,
} EAuthMeMouthStatus;

typedef enum _AUTHME_ID_CARD_METAL_TAG_STATUS : int
{
    eAuthMe_IDCardMetalTag_NotFound = 0,
    eAuthMe_IDCardMetalTag_Bright,
    eAuthMe_IDCardMetalTag_Dark,
} EAuthMeIDCardMetalTagStatus;

typedef struct _AUTHME_IMAGE
{
    EAuthMeColorFormat eFormat;
    int iWidth;
    int iHeight;
    unsigned long ulStride;
    void* pData;
} AuthMeImage;

typedef struct _AUTHME_ENGINE_DEBUG_INFO
{
    // ms
    float fPreProcTime;
    float fInferenceTime;
    float fPostProcTime;
} AuthMeEngineDebugInfo;

typedef struct _AUTHME_RECT_FLOAT
{
    float fLeft;
    float fTop;
    float fRight;
    float fBottom;
} AuthMeRectFloat;

typedef struct _AUTHME_FACE_INFO
{
    float fScore;
    float fMask;
    AuthMeRectFloat box;
    float afLandmark[10];
} AuthMeFaceInfo;

typedef struct _AUTHME_T_MRZ_FIELD
{
    char surname[40];
    char givenName[40];
    char birthDate[12];
    char expiryDate[12];
    char country[4];
    char documentNumber[12];
    char documentType[4];
    char sex[4];
    char nationality[4];
    char personalNumber[16];
} AuthMeMRZFieldTD3;



#ifdef __cplusplus
}
#endif