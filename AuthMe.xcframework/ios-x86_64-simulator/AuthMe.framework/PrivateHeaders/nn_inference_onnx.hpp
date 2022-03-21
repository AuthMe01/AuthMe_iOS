#pragma once
#include "nn_inference.hpp"
#include "onnxruntime_cxx_api.h"

namespace AuthMe
{

class CInference_ONNX : public IInferenceEngine
{
    public:
        CInference_ONNX();
        virtual ~CInference_ONNX();
        bool Initial(const std::string &strModelPath, const std::string &strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, const std::string &strHWAcceleration = "cpu") override;
        std::map<std::string, std::string> GetModelMetadata() const override;
        virtual std::map<std::string, std::vector<int64_t>> GetInputShape() const override;
        virtual std::map<std::string, std::vector<int64_t>> GetOutputShape() const override;
        void SetIOShape(const std::vector<std::pair<std::string, std::vector<int64_t>>>& vecInputShape,
                        const std::vector<std::pair<std::string, std::vector<int64_t>>>& vecOutputShape) override;
        std::string GetModelInfo() const override;
        void SetInput(const std::vector<TTensorInfo> &vecInfo) override;
        void SetOutput(const std::vector<TTensorInfo>& vecInfo) override;
        void Run() override;

    private:
        void CreateTensor(std::vector<Ort::Value> &vecTensor,
                          const std::vector<TTensorInfo>& vecTensorInfo,
                          const std::vector<std::pair<std::string, std::vector<int64_t>>>& vecShape,
                          size_t (Ort::Session::*pGetCount)() const,
                          Ort::TypeInfo(Ort::Session::*pGetTypeInfo)(size_t) const);
        template<typename T> Ort::Value GenTensor(Ort::MemoryInfo& memInfo, void* pData, const std::vector<int64_t>& shape);
        Ort::SessionOptions GenSessionOption(const std::string &strHWAcceleration);
        std::vector<std::string> GetNameFromSession(size_t (Ort::Session::*pGetCount)() const,
                char *(Ort::Session::*pGetName)(size_t, OrtAllocator *) const) const;
        std::string GetInputName(size_t idx) const;
        std::string GetOutputName(size_t idx) const;
        std::string GetString(char *(Ort::Session::*pFunc)(size_t, OrtAllocator *) const, size_t idx) const;

        std::string m_strHWAcceleration;
        std::unique_ptr<Ort::Env> m_pEnv;
        std::vector<std::pair<std::string, std::vector<int64_t>>> m_vecInputShape;
        std::vector<std::pair<std::string, std::vector<int64_t>>> m_vecOutputShape;
        std::unique_ptr<Ort::Session> m_pSession;
        std::vector<Ort::Value> m_vecInputTensors;
        std::vector<Ort::Value> m_vecOutputTensors;
};
}