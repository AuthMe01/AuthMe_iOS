#pragma once
#include <vector>
#include "engine_type.hpp"

namespace AuthMe
{

bool IsEncrypted(const std::vector<unsigned char>& buffer);
bool IsEncrypted(const void* pBuffer, size_t uiLength);

std::vector<unsigned char> EncryptModel(const std::string& strFilePath);
std::vector<unsigned char> EncryptModel(const std::vector<unsigned char>& plaintext, const EEngineFrameworkType eFramework);

bool DecryptModel(const std::string& strInputPath, std::vector<unsigned char>& plaintext, EEngineFrameworkType& eFramework);
bool DecryptModel(std::vector<unsigned char>& cipher, std::vector<unsigned char>& plaintext, EEngineFrameworkType& eFramework);
bool DecryptModel(const unsigned char* cipher, size_t uiLength, std::vector<unsigned char>& plaintext, EEngineFrameworkType& eFramework);

}
