#pragma once
#include "engine_service_type.h"
#include <string>

namespace AuthMe
{

EAuthMeSDKAuthStatus VerifySDK(const std::string& serviceCrt, const std::string& strJWTToken);

void SetPublicKeyForJson(const std::string& publicKey);

EAuthMeSDKAuthStatus GetAuthStatus();

}
