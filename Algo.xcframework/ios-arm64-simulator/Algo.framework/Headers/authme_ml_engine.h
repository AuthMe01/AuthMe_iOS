
#ifndef _AUTHME_ML_ENGINE_H_
#define _AUTHME_ML_ENGINE_H_

#include "authme_ml_engine_type.h"

#ifdef __cplusplus
extern "C" {
#endif

    // General APIs
    int authme_engine_verify(const char* serviceCrt, const char* token);
    int authme_engine_set_report_key(const char* publicKey);
    int authme_engine_get_log(const int logStringMaxLength, char* const logString);
    int authme_engine_get_version(char* const version);
    int authme_engine_get_size(const char* typeName);
    const char* authme_engine_get_model_name(const char* model);
    const char* authme_engine_get_message(const int returnCode);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Encryption APIs
    char* authme_encrypt_string(const char* plaintext, const char* publicKey);
    char* authme_decrypt_string(const char* cipherBase64, const char* privateKey);
    char* authme_encrypt_with_rsa_private_key(const char* plaintext);
    char* authme_decrypt_with_rsa_public_key(const char* encryptedText, const char* publickey);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Inference APIs
    int authme_inference_init(int* const contextId, const char* modelName, const char* modelPath);
    int authme_inference_init_binary(int* const contextId, const char* modelName, const void* data, const int size);
    int authme_inference_set_param(const int contextId, const InferenceParams* params);
    int authme_inference_exec(const int contextId, const AuthmeImg* image, int* const objNumber, ObjInfo* const objects);
    int authme_inference_free(const int contextId, const char* modelName);
    int authme_inference_get_version(const int contextId, const char* modelName, char* const version);
    int authme_inference_get_info(const int contextId, const char* modelName, const int jsonStringMaxLength, char* const jsonString);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Card OCR Service APIs
    int card_ocr_service_get_version(CardOCRModelVersion* const versions, int* const modelNumber);
    int card_ocr_service_init(int* const contextId, const CardOCRModels* models, const ServiceUIParams* uiParams, const ServiceROI* cardRoi, const char* targetCardType);
    int card_ocr_service_set_param(const int contextId, const CardOCRParams* params);
    int card_ocr_service_set_option(const int contextId, const char* option, const char* value);
    int card_ocr_service_exec(const int contextId, const AuthmeImg* image, CardOCRResult* const result);
    int card_ocr_service_stop(const int contextId);
    int card_ocr_service_get_info(const int contextId, const int jsonStringMaxLength, char* const jsonString);
    int card_ocr_service_get_debug_info(const int contextId, const CardOCRDebugInfoSetting* setting, CardOCRDebugInfo* const info);
    int card_ocr_service_free(const int contextId);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Face Anti-Spoofing Service APIs
    int fas_service_get_version(FASModelVersion* const versions, int* const modelNumber);
    int fas_service_init(int* contextId, const FASModels* models, const ServiceUIParams* uiParams, const FASStageSetting* settings);
    int fas_service_set_param(const int contextId, const FASParams* params);
    int fas_service_set_option(const int contextId, const char* option, const char* value);
    int fas_service_exec(const int contextId, const AuthmeImg* image, FASResult* const result);
    int fas_service_stop(const int contextId);
    int fas_service_get_info(const int contextId, const int jsonStringMaxLength, char* const jsonString);
    int fas_service_get_debug_info(const int contextId, const FASDebugInfoSetting* setting, FASDebugInfo* const info);
    int fas_service_free(const int contextId);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // IDCard Anti-Fraud Service APIs
    int idcard_antifraud_service_get_version(IDCardAntiFraudModelVersion* const versions, int* const modelNumber);
    int idcard_antifraud_service_init(int* contextId, const IDCardAntiFraudModels* models, const ServiceUIParams* uiParams, const ServiceROI* cardRoi, const IDCardAntiFraudStageSetting* settings);
    int idcard_antifraud_service_set_param(const int contextId, const IDCardAntiFraudParams* params);
    int idcard_antifraud_service_set_option(const int contextId, const char* option, const char* value);
    int idcard_antifraud_service_exec(const int contextId, const AuthmeImg* image, IDCardAntiFraudResult* const result);
    int idcard_antifraud_service_stop(const int contextId);
    int idcard_antifraud_service_get_info(const int contextId, const int jsonStringMaxLength, char* const jsonString);
    int idcard_antifraud_service_get_debug_info(const int contextId, const IDCardAntiFraudDebugInfoSetting* setting, IDCardAntiFraudDebugInfo* const info);
    int idcard_antifraud_service_free(const int contextId);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // MRZ Service APIs
    int mrz_service_get_version(MRZModelVersion* const versions, int* const modelNumber, const MRZType type);
    int mrz_service_init(int* const contextId, const MRZModels* models, const ServiceUIParams* uiParams, const ServiceROI* matchRoi);
    int mrz_service_set_param(const int contextId, const MRZParams* params);
    int mrz_service_set_option(const int contextId, const char* option, const char* value);
    int mrz_service_exec(const int contextId, const AuthmeImg* image, MRZResult* const result);
    int mrz_service_stop(const int contextId);
    int mrz_service_get_info(const int contextId, const int jsonStringMaxLength, char* const jsonString);
    int mrz_service_get_debug_info(const int contextId, const MRZDebugInfoSetting* setting, MRZDebugInfo* const info);
    int mrz_service_free(const int contextId);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif //_AUTHME_ML_ENGINE_H_
