#pragma once
#include <vector>
#include <string>

namespace AuthMe
{

std::string Base64Encode(const unsigned char* buf, unsigned int bufLen);

std::vector<unsigned char> Base64Decode(std::string const&);

}
