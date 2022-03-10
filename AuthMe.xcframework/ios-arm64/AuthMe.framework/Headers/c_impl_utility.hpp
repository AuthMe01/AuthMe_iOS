#pragma once
#include "engine_type.h"
#include "engine_error_code.h"
#include "utility_define.hpp"
#include "opencv2/core.hpp"
#include <iostream>

namespace AuthMe
{

inline cv::Rect2f GetCvRect(const AuthMeRectFloat& rect)
{
    return cv::Rect2f(cv::Point2f(rect.fLeft, rect.fTop), cv::Point2f(rect.fRight, rect.fBottom));
}

inline AuthMeRectFloat ToAuthMeRectFloat(const cv::Rect2f& rect)
{
    return AuthMeRectFloat
    {
        .fLeft = rect.tl().x,
        .fTop = rect.tl().y,
        .fRight = rect.br().x,
        .fBottom = rect.br().y
    };
}

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

cv::Mat GetCvMat_BGR(const AuthMeImage& image);

cv::Mat GetCvMat_RGB(const AuthMeImage& image);

cv::Size ToCv(const AuthMeSize& auSize);

}
