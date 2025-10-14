
#ifndef _AUTHME_ML_ENGINE_TYPE_H_
#define _AUTHME_ML_ENGINE_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------

typedef enum _AUTHME_ENGINE_RETUEN_CODE: int
{
    Authme_Engine_Success = 0,
    Authme_Engine_Failed,
    Authme_Engine_VersionNotSupported,
    Authme_Engine_Authorization_Pass,
    Authme_Engine_Authorization_Failed,
    Authme_Engine_ReadFileFailed,
    Authme_Engine_InvalidParams,
    Authme_Engine_InvalidStages,
    Authme_Engine_MissingConfig,
    Authme_Engine_InvalidUIParams,
    Authme_Engine_OutputArraySizeInvalid,
} AuthmeEngineReturnCode;

#define MAX_VERSION_LENGTH 20

typedef struct _AuthmePoint2f
{
    float x;
    float y;
} AuthmePoint2f;

#define MAX_ROI_POINT_NUMBER 8
typedef struct _ServiceROI
{
    int point_number;
    AuthmePoint2f points[MAX_ROI_POINT_NUMBER];
} ServiceROI;

typedef enum _ImgType
{
    IMAGE_TYPE_GRAY = 0,
    IMAGE_TYPE_BGR = 1,
    IMAGE_TYPE_RGB = 2,
    IMAGE_TYPE_RGBA = 3,
    //IMAGE_TYPE_YUV_YV12 = 4,
    //IMAGE_TYPE_YUV_NV12 = 5,
    //IMAGE_TYPE_YUV_I420 = 6,
    IMAGE_TYPE_RGBA_DEPTH_ANDROID = 10,
    IMAGE_TYPE_RGBA_DEPTH_IOS = 11, 
} ImgType;

typedef struct _AuthmeImg
{
    int width;
    int height;
    int step;
    int channels;
    ImgType type;
    unsigned char* data;    
    unsigned char* depth;
} AuthmeImg;

typedef struct _AuthmeSize
{
    int width;
    int height;
} AuthmeSize;

typedef struct _AuthmeLineFloat
{
    AuthmePoint2f p1;
    AuthmePoint2f p2;
} AuthmeLineFloat;

typedef struct _AuthmeRectFloat
{
    float x;
    float y;
    float width;
    float height;
} AuthmeRectFloat;

typedef struct _AuthmeQuadrilateral
{
    AuthmePoint2f p1;
    AuthmePoint2f p2;
    AuthmePoint2f p3;
    AuthmePoint2f p4;
} AuthmeQuadrilateral; // A polygon with four sides and four angles.

typedef struct _ServiceUIParams
{
    bool is_mirror;
    AuthmeSize size;
    AuthmeRectFloat rect;
} ServiceUIParams;

#define MAX_ENGINE_DEBUG_INFO_NAME_LEN 64
typedef struct _EngineDebugInfo
{
    char name[MAX_ENGINE_DEBUG_INFO_NAME_LEN];
    // ms
    float pre_proc_time;
    float inference_time;
    float post_proc_time;
} EngineDebugInfo;

#define MAX_MODEL_NAME_LEN 32
#define MAX_MODEL_VERSION_LEN 8

typedef struct _ModelVersion
{
    char name[MAX_MODEL_NAME_LEN];
    char version[MAX_MODEL_VERSION_LEN];
} ModelVersion;

typedef struct _ObjInfo
{
    AuthmePoint2f p0;
    AuthmePoint2f p1;
    AuthmePoint2f p2;
    AuthmePoint2f p3;
    float confidence;
    char name[MAX_MODEL_NAME_LEN];
} ObjInfo;

typedef enum _InferenceStatus
{
    ONNX_CPU = 0,
    //TRT_CPU = 10,
    //TRT_GPU = 11,
} InferenceTypes;

typedef struct _InferenceParams
{    
    InferenceTypes inference_type; // 0(default) = onnx + cpu
    int cpu_index; // -1(default) = all
} InferenceParams;

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define CARD_OCR_MODEL_NUM 4

typedef struct _CardOCRModelVersion
{
    ModelVersion models[CARD_OCR_MODEL_NUM];
} CardOCRModelVersion;

typedef struct _CardOCRModels
{
    int OCR_00;
    int OCR_01;
    int OCR_01_FB;
    int OCR_03;
} CardOCRModels;

typedef struct _CardOCRParams
{
    float card_classification_th;
    float image_reflective_mask_th;
    float image_reflective_trigger_th;
    float idcard_color_th;
    float image_blur_th;
    float card_match_th;
} CardOCRParams;

#define CARD_CLASS_ATTRIBUTE_COUNTRY_LEN 10
#define CARD_CLASS_ATTRIBUTE_DOCUMENT_LEN 50
#define CARD_CLASS_ATTRIBUTE_FRAGMENT_LEN 20
#define CARD_CLASS_ATTRIBUTE_VARIANCE_LEN 100
typedef struct _CARD_CLASS_ATTRIBUTE
{
    char country[CARD_CLASS_ATTRIBUTE_COUNTRY_LEN];
    char document[CARD_CLASS_ATTRIBUTE_DOCUMENT_LEN];
    char fragment[CARD_CLASS_ATTRIBUTE_FRAGMENT_LEN];
    char variance[CARD_CLASS_ATTRIBUTE_VARIANCE_LEN];
} CardClassAttribute;

#define CARD_CLASS_NAME_MAX_LEN 100
typedef struct _CardClassInfo
{
    char name[CARD_CLASS_NAME_MAX_LEN];
    CardClassAttribute attribute;
} CardClassInfo;

typedef struct _ImageReflectiveInfo
{
    float score;
} ImageReflectiveInfo;

typedef struct _ImageBlurInfo
{
    float score;
} ImageBlurInfo;

#define BARCODE_INFO_MAX_LEN 20
typedef struct _BarcodeInfo
{
    char field_1[BARCODE_INFO_MAX_LEN];
    char field_2[BARCODE_INFO_MAX_LEN];
} BarcodeInfo;

typedef struct _IDCardColorInfo
{
    float score;
} IDCardColorInfo;

typedef struct _CardOCRInfo
{
    AuthmeQuadrilateral card_vertices;
    AuthmeQuadrilateral card_match_vertices;
    float card_match_score;
    CardClassInfo card_class;
    ImageReflectiveInfo reflective;
    IDCardColorInfo color_detect;
    ImageBlurInfo blur;
    BarcodeInfo barcode;
} CardOCRInfo;

typedef enum _CardOCRStatus
{
    CardOCR_NoCard = 0,
    CardOCR_WrongCardType,
    CardOCR_PositionNotMatch,
    CardOCR_Reflective,
    CardOCR_Gray,
    CardOCR_Blur,
    CardOCR_Pass,
    CardOCR_Error,
    CardOCR_Motion,
} CardOCRStatus;

typedef struct _CardOCRResult
{
    CardOCRInfo info;
    CardOCRStatus status;
} CardOCRResult;

#define MAX_OPTION_VALUE_LEN 28
typedef struct _CardOCRDebugInfoSetting
{
    bool is_output_image;
    AuthmeImg image; // inout
    bool is_output_card_image;
    AuthmeImg card_image; // inout
    bool is_output_debug_info;
    bool is_output_service_ui_params;
    bool is_output_analysis_roi;
    bool is_output_params;
    bool is_output_option;
    char option[MAX_OPTION_VALUE_LEN];
} CardOCRDebugInfoSetting;

#define CARD_OCR_DEBUG_INFO_NUM 3
typedef struct _CardOCRDebugInfo
{
    EngineDebugInfo debug_info[CARD_OCR_DEBUG_INFO_NUM];
    ServiceUIParams ui_params;
    AuthmeRectFloat analysis_roi;
    CardOCRParams params;
    char value[MAX_OPTION_VALUE_LEN];
} CardOCRDebugInfo;

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define FAS_MODEL_NUM 3

typedef struct _FASModelVersion
{
    ModelVersion models[FAS_MODEL_NUM];
} FASModelVersion;

typedef struct _FASModels
{
    int FACE_00;
    int FACE_01;
    int FACE_02;
    //int FACE_03;
} FASModels;

typedef struct _FASParams
{
    float face_detect_th;
    float mask_th;
    float eye_th;
    float mouth_th;
    float fas_th;
    int depth_level;
    float mini_fas_th;
    int fas_accumulative_num;
    int timeout_sec;
    int fas_timeout_sec;
    AuthmeRectFloat face_roi;
    float not_at_center_th;
    float face_too_small_th;
    float face_too_large_th;
} FASParams;

typedef enum _FASStage
{
    FAS_Stage_Passive = 0,
    FAS_Stage_OpenMouth,
    FAS_Stage_CloseMouth,
    FAS_Stage_Smile,
    FAS_Stage_FaceScale,
    FAS_Stage_Done,
} FASStage;

typedef struct _FASStageParams
{
    int apply_fas;
    int frame_num;
    float threshold;
} FASStageParam;

#define FAS_STAGE_MAX_NUM 8
typedef struct _FASStageSetting
{
    int stage_num;
    FASStage stages[FAS_STAGE_MAX_NUM];
    bool is_setting_params[FAS_STAGE_MAX_NUM];
    FASStageParam params[FAS_STAGE_MAX_NUM];
} FASStageSetting;

#define FACE_INFO_LANDMARK_LEN 10
#define FACE_INFO_CLASS_NUM 50
typedef struct _FaceInfo
{
    float score;
    AuthmeRectFloat box;
    float landmark[FACE_INFO_LANDMARK_LEN]; //x1, y1, x2, y2, ...
    float classes[FACE_INFO_CLASS_NUM];
    int class_num;
} FaceInfo;

typedef enum _EyeStatus
{
    Eye_Close = 0,
    Eye_Open,
} EyeStatus;

typedef struct _EyeInfo
{
    EyeStatus status;
    float score;
} EyeInfo;

typedef enum _MouthStatus
{
    Mouth_Close = 0,
    Mouth_Open,
} MouthStatus;

typedef struct _MouthInfo
{
    MouthStatus status;
    float score;
} MouthInfo;

typedef enum FacePose
{
    FacePose_Unknown = -1,
    FacePose_LeftProfile = 0,
    FacePose_LeftFrontal,
    FacePose_Frontal,
    FacePose_RightFrontal,
    FacePose_RightProfile,
    FacePose_UpFrontal,
    FacePose_DownFrontal,
} FacePose;

typedef struct _FacePoseInfo
{
    FacePose pose;
} FacePoseInfo;

typedef enum _FaceAntiSpoofingStatus
{
    FaceAntiSpoofing_FrameNotEnough = 0,
    FaceAntiSpoofing_Real,
    FaceAntiSpoofing_Spoof,
    FaceAntiSpoofing_DepthFake,
    FaceAntiSpoofing_Error,
} FaceAntiSpoofingStatus;

typedef struct _MiniFASInfo
{
    FaceAntiSpoofingStatus status;
    float score;
} MiniFASInfo;

#define FAS_INFO_SCORE_LEN 20
#define FAS_INFO_ACCUMULATE_SCORE_LEN 20
typedef struct _FASInfo
{
    FaceAntiSpoofingStatus status;
    int class_num;
    float score[FAS_INFO_SCORE_LEN];
    float accumulate_score[FAS_INFO_ACCUMULATE_SCORE_LEN];
    float depth_score;
} FASInfo;

#define FAS_SERVICE_INFO_LANDMARK106_LEN 212
typedef struct _FASServiceInfo
{
    FaceInfo faceInfo;
    float landmark106[FAS_SERVICE_INFO_LANDMARK106_LEN];
    EyeInfo eyeInfo;
    MouthInfo mouthInfo;
    FacePoseInfo poseInfo;
    MiniFASInfo miniFASInfo;
    FASInfo fasInfo;
} FASServiceInfo;

typedef enum _FASStatus
{
    FAS_Failed = 0,
    FAS_NoFace,
    FAS_FaceNotAtCenter,
    FAS_FaceTooSmall,
    FAS_FaceTooLarge,
    FAS_NeedFaceToCamera,
    FAS_FaceMasked,
    FAS_NeedOpenMouth,
    FAS_NeedCloseMouth,
    FAS_NeedOpenEyes,
    FAS_NeedSmile,
    FAS_DepthFake,
    FAS_NeedMoreFrame,
    FAS_Pass,
    FAS_Error,
} FASStatus;

typedef struct _FASResult
{
    bool is_key_frame;
    float stage_score;
    FASServiceInfo info;
    FASStatus status;
    FASStage stage;
} FASResult;

typedef struct _FASDebugInfoSetting
{
    bool is_output_image;
    AuthmeImg image; // inout
    bool is_output_debug_info;
    bool is_output_service_ui_params;
    bool is_output_params;
    bool is_output_face_roi;
    bool is_output_stage_setting;
    bool is_output_option;
    char option[MAX_OPTION_VALUE_LEN];
} FASDebugInfoSetting;

#define FAS_DEBUG_INFO_NUM 4
typedef struct _FASDebugInfo
{
    EngineDebugInfo debug_info[FAS_DEBUG_INFO_NUM];
    ServiceUIParams ui_params;
    FASParams params;
    AuthmeRectFloat face_roi;
    FASStageSetting settings;
    char value[MAX_OPTION_VALUE_LEN];
} FASDebugInfo;

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define IDCARD_ANTIFRAUD_MODEL_NUM 5

typedef struct _IDcardAntiFraudModelVersion
{
    ModelVersion models[IDCARD_ANTIFRAUD_MODEL_NUM];
} IDCardAntiFraudModelVersion;

typedef struct _IDCardAntiFraudModels
{
    int OCR_00;
    int OCR_01;
    int OCR_01_FB;
    int IDCardAntiFraud_00;
    int OCR_03;
} IDCardAntiFraudModels;

typedef struct _IDCardAntiFraudParams
{
    float card_classification_th;
    float metal_tag_detection_th;
    float image_reflective_th;
    float image_blur_th;
    float image_thickness_th;
    float idcard_color_th;
    int timeout_sec;
    int metal_tag_valid_count_th;
    int enable_card_in_roi;
    int card_match_frame_num;
    float card_match_th;
    float card_deformation_th;
    float metal_tag_reflection_th;
    float metal_tag_reflection_density_th;
} IDCardAntiFraudParams;

typedef enum _IDCardAntiFraudStage
{
    IDCardFraud_Stage_Frontal = 0,
    IDCardFraud_Stage_Up,
    IDCardFraud_Stage_Down,
    IDCardFraud_Stage_Left,
    IDCardFraud_Stage_Right,
    IDCardFraud_Stage_IgnoreCardMatch,
    IDCardFraud_Stage_Done,
} IDCardAntiFraudStage;

#define IDCardAntiFraud_STAGE_MAX_NUM 8
typedef struct _IDCardAntiFraudStageSetting
{
    int stage_num;
    IDCardAntiFraudStage stages[IDCardAntiFraud_STAGE_MAX_NUM];
} IDCardAntiFraudStageSetting;

typedef enum _CardMatchStatus
{
    CardMatch_Mismatch = 0,
    CardMatch_NeedMoreFrame,
    CardMatch_CardNotInAnalysisROI,
    CardMatch_CardNotInROI,
    CardMatch_CardTooSmall,
    CardMatch_NeedMoreDeformation,
    CardMatch_NeedHoldCard,
    CardMatch_None,
    CardMatch_Match,
} CardMatchStatus;

typedef struct _ImageThicknessInfo
{
    float score;
} ImageThicknessInfo;

typedef enum _IDCardMetalTagStatus
{
    IDCardMetalTag_NotFound = 0,
    IDCardMetalTag_Bright,
    IDCardMetalTag_Dark,
} IDCardMetalTagStatus;

#define METAL_TAG_REGION_NUM 3
typedef struct _MetalTagInfo
{
    IDCardMetalTagStatus status[METAL_TAG_REGION_NUM];
    AuthmeLineFloat line[METAL_TAG_REGION_NUM];
    bool has_anti_feature;
} MetalTagInfo;

typedef struct _IDCardAntiFraudInfo
{
    AuthmeQuadrilateral card_vertices;
    AuthmeQuadrilateral card_match_vertices;
    int frame_index;
    float card_match_score;
    float card_deformation;
    bool is_card_inside_roi;
    bool is_card_cut_by_camera;
    CardMatchStatus card_match_status;
    ImageReflectiveInfo reflective;
    ImageBlurInfo blur;
    ImageThicknessInfo thickness;
    IDCardColorInfo color_detect;
    MetalTagInfo metal_tag;
    ImageReflectiveInfo metal_tag_reflection;
    CardClassInfo card_class;
} IDCardAntiFraudInfo;

typedef struct _IDCardAntiFraudStatistics
{
    int valid_metal_tag_count;
} IDCardAntiFraudStatistics;

typedef enum _IDCardAntiFraudStatus
{
    IDCardFraud_Pass = 0,
    IDCardFraud_Failed,
    IDCardFraud_NoCard,
    IDCardFraud_WrongCardType,
    IDCardFraud_CardCutByCamera,
    IDCardFraud_CardThicknessFailed,
    IDCardFraud_Reflective,
    IDCardFraud_Blur,
    IDCardFraud_CardNotInROI,
    IDCardFraud_CardTooSmall,
    IDCardFraud_NeedDeformationFrontal,
    IDCardFraud_NeedDeformationLeft,
    IDCardFraud_NeedDeformationRight,
    IDCardFraud_NeedDeformationUp,
    IDCardFraud_NeedDeformationDown,
    IDCardFraud_NeedHoldCard,
    IDCardFraud_StagePass,
    IDCardFraud_NeedMoreFrame,
    IDCardFraud_Undefined,
    IDCardFraud_Error,
    IDCardFraud_Gray,
    IDCardFraud_AntiFraudFeatureDetect,
    IDCardFraud_PositionNotMatch,
} IDCardAntiFraudStatus;

typedef struct _IDCardAntiFraudResult
{
    bool is_key_frame;
    IDCardAntiFraudInfo info;
    IDCardAntiFraudStatistics statistics;
    IDCardAntiFraudStage stage;
    IDCardAntiFraudStatus status;
} IDCardAntiFraudResult;

typedef struct _IDCardAntiFraudDebugInfoSetting
{
    bool is_output_image;
    AuthmeImg image; // inout
    bool is_output_debug_info;
    bool is_output_service_ui_params;
    bool is_output_params;
    bool is_output_stage_setting;
    bool is_output_analysis_roi;
    bool is_output_card_match_roi;
    bool is_output_option;
    char option[MAX_OPTION_VALUE_LEN];
} IDCardAntiFraudDebugInfoSetting;

#define IDCARD_ANTIFRAUD_DEBUG_INFO_NUM 4
#define IDCARD_ANTIFRAUD_DEBUG_INFO_STAGE_SETTING_MAX 8
typedef struct _IDCardAntiFraudDebugInfo
{
    EngineDebugInfo debug_info[IDCARD_ANTIFRAUD_DEBUG_INFO_NUM];
    ServiceUIParams ui_params;
    IDCardAntiFraudParams params;
    IDCardAntiFraudStageSetting settings;
    AuthmeRectFloat analysis_roi;
    AuthmeQuadrilateral card_match_roi;
    char value[MAX_OPTION_VALUE_LEN];
} IDCardAntiFraudDebugInfo;

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define MRZ_MODEL_NUM 6

typedef struct _MRZModelVersion
{
    ModelVersion models[MRZ_MODEL_NUM];
} MRZModelVersion;

typedef struct _MRZModels
{
    int OCR_00;
    int OCR_01;
    int OCR_01_FB;
    int OCR_03;
    int MRZ_00;
    int MRZ_01;
} MRZModels;

typedef struct _MRZParams
{
    float image_reflective_mask_th;
    float image_reflective_trigger_th;
    float image_blur_th;
    float position_match_th;
    float card_classification_th;
} MRZParams;

typedef enum _MRZRecogStatus
{
    MRZ_Recog_Success = 0,
    MRZ_Recog_WrongFormat,
} MRZRecogStatus;

#define MRZ_INFO_MRZ_VERTICES_NUM 2
typedef struct _MRZInfo
{
    float position_match_score;
    AuthmeQuadrilateral card_vertices;
    AuthmeQuadrilateral mrz_vertices[MRZ_INFO_MRZ_VERTICES_NUM];
    CardClassInfo card_class;
    ImageReflectiveInfo reflective;
    ImageBlurInfo blur;
    MRZRecogStatus recog_status;
} MRZInfo;

typedef enum _MRZStatus
{
    MRZ_NotFound = 0,
    MRZ_NotAligned,
    MRZ_Reflective,
    MRZ_Blur,
    MRZ_WrongCardType,
    MRZ_MRZNotFound,
    MRZ_RecogFailed,
    MRZ_Success,
    MRZ_Error,
} MRZStatus;

#define MRZ_FIELD_SURNAME_LEN 40
#define MRZ_FIELD_GIVEN_NAME_LEN 40
#define MRZ_FIELD_CHAR_12 12
#define MRZ_FIELD_CHAR_16 16
#define MRZ_FIELD_CHAR_4 4
typedef struct _MRZField
{
    char surname[MRZ_FIELD_SURNAME_LEN];
    char given_name[MRZ_FIELD_GIVEN_NAME_LEN];
    char birth_date[MRZ_FIELD_CHAR_12];
    char expiry_date[MRZ_FIELD_CHAR_12];
    char country[MRZ_FIELD_CHAR_4];
    char document_number[MRZ_FIELD_CHAR_12];
    char document_type[MRZ_FIELD_CHAR_4];
    char sex[MRZ_FIELD_CHAR_4];
    char nationality[MRZ_FIELD_CHAR_4];
    char personal_number[MRZ_FIELD_CHAR_16];
    char document_number_check_digit[MRZ_FIELD_CHAR_4];
    char birth_date_check_digit[MRZ_FIELD_CHAR_4];
    char expiry_date_check_digit[MRZ_FIELD_CHAR_4];
    char optional_data_check_digit[MRZ_FIELD_CHAR_4];
    char overall_check_digit[MRZ_FIELD_CHAR_4];
} MRZField;

typedef struct _MRZResult
{
    MRZInfo info;
    MRZStatus status;
    MRZField field;
} MRZResult;

typedef struct _MRZDebugInfoSetting
{
    bool is_output_image;
    AuthmeImg image; // inout
    bool is_output_card_image;
    AuthmeImg card_image; // inout
    bool is_output_debug_info;
    bool is_output_service_ui_params;
    bool is_output_params;
    bool is_output_match_roi;
    bool is_output_option;
    char option[MAX_OPTION_VALUE_LEN];
} MRZDebugInfoSetting;

#define MRZ_DEBUG_INFO_NUM 5
typedef struct _MRZDebugInfo
{
    EngineDebugInfo debug_info[MRZ_DEBUG_INFO_NUM];
    ServiceUIParams ui_params;    
    MRZParams params;
    AuthmeQuadrilateral match_roi;
    char value[MAX_OPTION_VALUE_LEN];
} MRZDebugInfo;

typedef enum _MRZType
{
    MRZ_TD1 = 0,
    MRZ_TD3
} MRZType;

#ifdef __cplusplus
}
#endif

#endif //_AUTHME_ML_ENGINE_TYPE_H_
