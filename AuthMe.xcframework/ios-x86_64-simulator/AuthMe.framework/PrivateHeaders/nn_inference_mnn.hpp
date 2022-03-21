#pragma once
#include "nn_inference.hpp"
#include "MNN/Interpreter.hpp"

namespace AuthMe
{

class CInference_MNN : public IInferenceEngine
{
    public:
        CInference_MNN();
        virtual ~CInference_MNN();
        bool Initial(const std::string &strModelPath, const std::string &strHWAcceleration = "cpu") override;
        bool Initial(const void *pData, size_t uiLength, const std::string &strHWAcceleration = "cpu") override;
        std::map<std::string, std::string> GetModelMetadata() const override;
        std::map<std::string, std::vector<int64_t>> GetInputShape() const override;
        std::map<std::string, std::vector<int64_t>> GetOutputShape() const override;
        void SetIOShape(const std::vector<std::pair<std::string, std::vector<int64_t>>>& vecInputShape,
                        const std::vector<std::pair<std::string, std::vector<int64_t>>>& vecOutputShape) override;
        std::string GetModelInfo() const override;
        void SetInput(const std::vector<TTensorInfo> &vecInput) override;
        void SetOutput(const std::vector<TTensorInfo>& vecOutput) override;
        void Run() override;

    private:
        MNN::ScheduleConfig GenConfig(const std::string &strHWAcceleration);

        std::string m_strHWAcceleration;
        MNN::Interpreter* m_pInterpreter = nullptr;
        MNN::Session* m_pSession = nullptr;
        std::vector<TTensorInfo> m_vecOutput;
};
}
