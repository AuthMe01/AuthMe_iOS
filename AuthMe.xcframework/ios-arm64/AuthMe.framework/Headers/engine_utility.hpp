#pragma once
#include "nn_inference.hpp"

namespace AuthMe
{

typedef struct T_MAPPING_SCORE
{
    std::vector<double> vecSrc;
    std::vector<double> vecDst;
} TMappingScore;

typedef struct T_MODEL_METADATA
{
    std::unique_ptr<float> pfThreshold;
    std::string strDate;
    std::string strUDF;
    TMappingScore tMappingScore;
} TModelMetadata;

// for encrypted and plaintext model
bool InitialEngine(std::unique_ptr<IInferenceEngine>& pEngine, const std::string& strModelPath, const std::string strHWAcceleration);

// for encrypted model
bool InitialEngine(std::unique_ptr<IInferenceEngine>& pEngine, const void *pData, size_t uiLength, const std::string strHWAcceleration);

// for plaintext model
bool InitialEngine(std::unique_ptr<IInferenceEngine>& pEngine, const void *pData, size_t uiLength,
                   EEngineFrameworkType eFramework, const std::string strHWAcceleration);

cv::Size GetSize(const std::vector<int64_t>& vecShape);

int GetChannel(const std::vector<int64_t>& vecShape);

void SetBatchIfSupported(std::vector<int64_t>& vecShape, int64_t batchSize);

TModelMetadata ParseModelMetadata(const std::map<std::string, std::string>& mapMetadata);

}