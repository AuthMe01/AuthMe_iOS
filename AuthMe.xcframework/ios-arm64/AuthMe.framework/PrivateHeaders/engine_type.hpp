#pragma once
#include <vector>
#include "opencv2/core.hpp"

namespace AuthMe
{

typedef enum
{
    eEngineFramework_MNN,
    eEngineFramework_ORT,
    eEngineFramework_Invalid,
} EEngineFrameworkType;

typedef enum
{
    eMRZ_Success = 0,
    eMRZ_WrongFormat,
} EMRZRecogStatus;

typedef enum E_FACE_POSE : int
{
    eFacePose_Unknown = -1,
    eFacePose_LeftProfile = 0,
    eFacePose_LeftFrontal,
    eFacePose_Frontal,
    eFacePose_RightFrontal,
    eFacePose_RightProfile,
    eFacePose_UpFrontal,
    eFacePose_DownFrontal,
} EFacePose;

typedef enum E_EYE_STATUS : int
{
    eEye_Close = 0,
    eEye_Open,
} EEyeStatus;

typedef enum E_MOUTH_STATUS : int
{
    eMouth_Close = 0,
    eMouth_Open,
} EMouthStatus;

typedef enum E_LASER_TAG_STATUS : int
{
    eLaserTag_NoTag = 0,
    eLaserTag_HasTag,
    eLaserTag_Others,
} ELaserTagStatus;

typedef enum E_TWIWAN_HOLE_STATUS : int
{
    eTaiwanHole_NotFound = 0,
    eTaiwanHole_Found,
} ETaiwanHoleStatus;

typedef enum E_ID_CARD_METAL_TAG_STATUS : int
{
    eIDCardMetalTag_NotFound = 0,
    eIDCardMetalTag_Bright,
    eIDCardMetalTag_Dark,
} EIDCardMetalTagStatus;

typedef struct T_ENGINE_DEBUG_INFO
{
    // ms
    float fPreProcTime = 0.0f;
    float fInferenceTime = 0.0f;
    float fPostProcTime = 0.0f;
} TEngineDebugInfo;

typedef struct T_FACE_INFO
{
    float fScore = 0.0f;
    float fMask = 0.0f;
    cv::Rect2f box;
    std::vector<cv::Point2f> vecLandmark;
} TFaceInfo;

typedef struct T_MRZ_FIELD_TD3
{
    std::string surname;
    std::string givenName;
    std::string birthDate;
    std::string expiryDate;
    std::string country;
    std::string documentNumber;
    std::string documentType;
    std::string sex;
    std::string nationality;
    std::string personalNumber;
} TMRZFieldTD3;
}


