#pragma once

#if __cplusplus >= 202002L
// C++20 (and later) code
#define DEFAULT_COMPARISON(typeName) bool operator==(const typeName&) const = default;
#else
#define DEFAULT_COMPARISON(typeName)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _E_AUTHME_COLOR_FORMAT
{
    eAuthMe_ColorFormat_Invalid = 0,
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


#define CARD_CLASS_TAG(decorate) \
    decorate(Invalid, = -1) \
    decorate(Background) \
    decorate(Unknown) \
    decorate(Passport) \
    decorate(TWN_IDCard_Front) \
    decorate(TWN_IDCard_Back) \
    decorate(TWN_DriverLicense_Front) \
    decorate(TWN_DriverLicense_Back) \
    decorate(TWN_Resident_Front) \
    decorate(TWN_Resident_Back) \
    decorate(TWN_Health_Front) \
    decorate(TWN_VehiclesLicense_Front)


#define CARD_CLASS_PREFIX(name, ...) eAuthMe_Card_##name __VA_ARGS__,
typedef enum _E_AUTHME_CARD_CLASS : int
{
    CARD_CLASS_TAG(CARD_CLASS_PREFIX)
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

typedef enum
{
    eFaceClass_Glass,
    eFaceClass_SunGlass,
    eFaceClass_HairCover,
    eFaceClass_MaskCover,
    eFaceClass_OtherCover,
    eFaceClass_HardToRecog,
    eFaceClass_TotalNum,
} EFaceClassStatus;

typedef struct _AUTHME_IMAGE
{
    EAuthMeColorFormat eFormat;
    int iWidth;
    int iHeight;
    unsigned long ulStride;
    void* pData;
    DEFAULT_COMPARISON(_AUTHME_IMAGE)
} AuthMeImage;

typedef struct _AUTHME_ENGINE_DEBUG_INFO
{
    // ms
    char moduleName[64];
    float fPreProcTime;
    float fInferenceTime;
    float fPostProcTime;
} AuthMeEngineDebugInfo;

typedef struct _AUTHME_ENGINE_DEBUG_INFO_LIST
{
    const AuthMeEngineDebugInfo *vecDbgInfo;
    int len;
} AuthMeEngineDebugInfoList;

typedef struct _AUTHME_RECT_FLOAT
{
    float fLeft;
    float fTop;
    float fRight;
    float fBottom;
    DEFAULT_COMPARISON(_AUTHME_RECT_FLOAT)
} AuthMeRectFloat;

typedef struct _AUTHME_SIZE
{
    int iWidth;
    int iHeight;
    DEFAULT_COMPARISON(_AUTHME_SIZE)
} AuthMeSize;

typedef struct _AUTHME_POINT_FLOAT
{
    float fX;
    float fY;
    DEFAULT_COMPARISON(_AUTHME_POINT_FLOAT)
} AuthMePointFloat;

typedef struct _AUTHME_FACE_INFO
{
    float fScore;
    AuthMeRectFloat box;
    float afLandmark[10]; //x1, y1, x2, y2, ...
    float afClasses[6];
    DEFAULT_COMPARISON(_AUTHME_FACE_INFO)
} AuthMeFaceInfo;


#define MRZ_FILED_TD3_CONTENT(decorate) \
    decorate(char, surname, 40) \
    decorate(char, givenName, 40) \
    decorate(char, birthDate, 12) \
    decorate(char, expiryDate, 12) \
    decorate(char, country, 4) \
    decorate(char, documentNumber, 12) \
    decorate(char, documentType, 4) \
    decorate(char, sex, 4) \
    decorate(char, nationality, 4) \
    decorate(char, personalNumber, 16)

#define IMPL_FIELD_TD3(type, name, size) type name[size];

typedef struct _AUTHME_T_MRZ_FIELD
{
    MRZ_FILED_TD3_CONTENT(IMPL_FIELD_TD3)
    DEFAULT_COMPARISON(_AUTHME_T_MRZ_FIELD)
}
AuthMeMRZFieldTD3;

#ifdef __cplusplus
}
#endif