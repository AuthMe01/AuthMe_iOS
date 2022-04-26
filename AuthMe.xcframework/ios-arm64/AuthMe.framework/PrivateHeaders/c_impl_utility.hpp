#pragma once
#include "engine_type.h"
#include "engine_type_v3.h"
#include "engine_error_code.h"
#include "utility_define.hpp"
#include "opencv2/core.hpp"

#include <iostream>
#include "utility.hpp"
#include "utility_algorithm.hpp"
#include "utility_format_adapter.hpp"

namespace AuthMe
{

template<typename T>
EAuthMeEngineReturnCode CreateDetector(long* pHandle, T CreatFunc())
{
    if (pHandle == NULL)
    {
        return eAuthMe_Engine_Failed;
    }

    auto pDetector = CreatFunc();

    if (pDetector == nullptr)
    {
        *pHandle = 0;
        return eAuthMe_Engine_Failed;
    }

    *pHandle = reinterpret_cast<long>(pDetector);
    return eAuthMe_Engine_Success;
}

template<typename T>
EAuthMeEngineReturnCode InitialDetector(long handle, const char* szModelPath)
{
    if (handle == 0)
    {
        return eAuthMe_Engine_Failed;
    }

    try
    {
        auto pDetector = reinterpret_cast<T*>(handle);
        return pDetector->Initial(szModelPath) ? eAuthMe_Engine_Success : eAuthMe_Engine_Failed;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
}
template<typename T>
const char* GetModelInfo(long handle)
{
    static std::string strInfo;
    auto pDetector = reinterpret_cast<T*>(handle);
    strInfo = pDetector->GetModelInfo();
    return strInfo.c_str();
}

template<typename T>
EAuthMeEngineReturnCode ReleaseDetector(long handle)
{
    if (handle == 0)
    {
        return eAuthMe_Engine_Failed;
    }

    try
    {
        delete reinterpret_cast<T*>(handle);

        return eAuthMe_Engine_Success;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
}

template<typename T>
EAuthMeEngineReturnCode SetThreshold(long handle, float fThreshold)
{
    if (handle == 0)
    {
        return eAuthMe_Engine_Failed;
    }

    try
    {
        auto pDetector = reinterpret_cast<T*>(handle);
        pDetector->SetThreshold(fThreshold);
        return eAuthMe_Engine_Success;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
}

template<typename T>
float GetThreshold(long handle)
{
    if (handle == 0)
    {
        return 0.0f;
    }

    try
    {
        auto pDetector = reinterpret_cast<T*>(handle);
        return pDetector->GetThreshold();
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return 0.0f;
}

template<typename ServiceType>
EAuthMeEngineReturnCode GetModelVersion(AuthMeModelVersion** ppVersion, int *piModelNum)
{
    try
    {
        if (ppVersion == NULL || piModelNum == NULL)
        {
            return eAuthMe_Engine_Failed;
        }

        auto vecVersion = ServiceType::GetModelVersion();

        *piModelNum = static_cast<int>(vecVersion.size());
        *ppVersion = new AuthMeModelVersion[vecVersion.size()];

        memcpy(*ppVersion, vecVersion.data(), vecVersion.size() * sizeof(AuthMeModelVersion));

        return eAuthMe_Engine_Success;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
}

cv::Mat GetCvMat_BGR(const AuthMeImage& image);

cv::Mat GetCvMat_RGB(const AuthMeImage& image);

cv::Size ToCv(const AuthMeSize& auSize);

cv::Rect2f ToCv(const AuthMeRectFloat& auRect);

}
