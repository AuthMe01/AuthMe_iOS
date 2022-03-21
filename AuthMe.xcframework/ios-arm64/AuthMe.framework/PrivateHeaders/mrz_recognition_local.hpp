#include "mrz_recognition.hpp"
#include "nn_inference.hpp"

namespace AuthMe
{

class CMRZRecognition : public IMRZRecognition
{
    public:
        bool Initial(const std::string& strModelPath, const std::string strHWAcceleration = "cpu") override;

        bool Initial(const void *pData, size_t uiLength, const std::string strHWAcceleration = "cpu") override;

        bool Initial(const void *pData, size_t uiLength, EEngineFrameworkType eFramework, const std::string strHWAcceleration = "cpu") override;

        // input image for mat should be BGR
        EMRZRecogStatus Run(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecVertices, TMRZFieldTD3& tField, TEngineDebugInfo* pInfo = nullptr) override;

        std::string GetModelInfo() const override;

    private:
        cv::Mat Preprocess(const cv::Mat& inputImage, const std::vector<cv::Point2f>& vecVertices);
        bool Postprocess(const std::vector<int64_t>& vecOutput, TMRZFieldTD3& tField);

        void ReviseLine1(std::string& str);
        void ReviseLine2(std::string& str);
        void TextMapping(std::string& str);
        bool ParseField(const std::vector<std::string>& vecCode, TMRZFieldTD3 &tField);
        void ReplaceDigits(std::string::iterator itBeg, std::string::iterator itEnd);
        void ReplaceLetters(std::string::iterator itBeg, std::string::iterator itEnd);
        void ReplaceSex(std::string::iterator itBeg, std::string::iterator itEnd);
        std::vector<char> CreateTextMappingTable();

        std::string ParseString(std::string str);
        void ParseName(const std::string& str, std::string& surname, std::string& givenName);
        std::string ParseDate(const std::string& str, int iShift = 0);


        std::unique_ptr<IInferenceEngine> m_pEngine = nullptr;
};

}