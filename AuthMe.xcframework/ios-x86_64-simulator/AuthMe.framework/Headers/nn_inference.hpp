#pragma once
#include <string>
#include <vector>
#include <memory>
#include "engine_type.hpp"

namespace AuthMe
{

typedef struct T_TENSOR_INFO
{
    std::string strName = "";
    void* pData = nullptr;
} TTensorInfo;

class IInferenceEngine
{
    public:
        virtual ~IInferenceEngine() {};

        // strHWAcceleration: "cpu", "cuda", "tensorrt"
        virtual bool Initial(const std::string &strModelName, const std::string &strHWAcceleration = "cpu") = 0;
        virtual bool Initial(const void *pData, size_t uiLength, const std::string &strHWAcceleration = "cpu") = 0;
        virtual void SetIOShape(const std::vector<std::pair<std::string, std::vector<int64_t>>>& vecInputShape,
                                const std::vector<std::pair<std::string, std::vector<int64_t>>>& vecOutputShape) = 0;
        virtual std::string GetModelInfo() const = 0;
        virtual void SetInput(const std::vector<TTensorInfo>& vecInput) = 0;
        virtual void SetOutput(const std::vector<TTensorInfo>& vecOutput) = 0;
        virtual void Run() = 0;
};

std::unique_ptr<IInferenceEngine> CreateInferEngine(EEngineFrameworkType eFramework);

}
