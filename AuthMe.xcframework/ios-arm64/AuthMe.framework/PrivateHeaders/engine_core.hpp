#pragma once
#include <string>
#include <chrono>
#include "engine_error_code.h"

namespace AuthMe
{

bool InitialEngine();

void SetAuthorizationCheckPeriod(std::chrono::seconds time);

EAuthMeEngineReturnCode EngineAuthorization(const std::string& token, const std::string key = "");

bool IsLibAuthorized();

bool ReleaseEngine();

}