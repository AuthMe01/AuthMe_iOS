#pragma once
#include "engine_type.h"
#include "engine_service_type.h"
#include "engine_error_code.h"
#include "utility_define.hpp"
#include "opencv2/core.hpp"

#include <iostream>
#include "utility.hpp"
#include "utility_algorithm.hpp"
#include "utility_format_adapter.hpp"

namespace AuthMe
{

static inline EAuthMeEngineReturnCode CheckNotZero()
{
    return eAuthMe_Engine_Success;
}

template<typename T, typename ...Args>
EAuthMeEngineReturnCode CheckNotZero(const T& param, Args... args)
{
    if (param == 0)
    {
        return eAuthMe_Engine_Failed;
    }

    return CheckNotZero(args...);
}

#define CheckParamsNoneZero(...) do {if (CheckNotZero(__VA_ARGS__) == eAuthMe_Engine_Failed) return eAuthMe_Engine_Failed;} while(0)

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
        return pDetector->Initial(szModelPath);
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
}

template<class ObjectType, typename T>
EAuthMeEngineReturnCode InitialService(long handle, const T* pParams)
{
    if (handle == 0 || pParams == NULL)
    {
        return eAuthMe_Engine_Failed;
    }

    try
    {
        auto pDetector = reinterpret_cast<ObjectType*>(handle);
        return pDetector->Initial(*pParams) ? eAuthMe_Engine_Success : eAuthMe_Engine_Failed;
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

template<class ObjectType, typename ...FuncArgs, typename ...Args>
EAuthMeEngineReturnCode CallNoReturn(long handle, void (ObjectType::*Func)(FuncArgs...), Args... args)
{
    if (handle == 0)
    {
        return eAuthMe_Engine_Failed;
    }

    try
    {
        auto pObj = reinterpret_cast<ObjectType*>(handle);
        (pObj->*Func)(args...);

        return eAuthMe_Engine_Success;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
}

template<class ObjectType, typename ReturnType, typename ...FuncArgs, typename ...Args>
ReturnType CallWithReturn(long handle, ReturnType(ObjectType::*Func)(FuncArgs...)const, ReturnType defaultValue, Args... args)
{
    if (handle == 0)
    {
        return defaultValue;
    }

    try
    {
        auto pObj = reinterpret_cast<ObjectType*>(handle);
        return (pObj->*Func)(args...);
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return defaultValue;
}

template<class ObjectType, typename ReturnType>
ReturnType CallWithReturn(long handle, ReturnType(ObjectType::*Func)()const)
{
    return CallWithReturn(handle, Func, ReturnType{});
}

template<class ObjectType, typename ReturnType, typename ...FuncArgs, typename ...Args>
ReturnType CallWithReturn(long handle, ReturnType(ObjectType::*Func)(FuncArgs...), ReturnType defaultValue, Args... args)
{
    if (handle == 0)
    {
        return defaultValue;
    }

    try
    {
        auto pObj = reinterpret_cast<ObjectType*>(handle);
        return (pObj->*Func)(args...);
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return defaultValue;
}

template<class ObjectType, typename ReturnType>
ReturnType CallWithReturn(long handle, ReturnType(ObjectType::*Func)())
{
    return CallWithReturn(handle, Func, ReturnType{});
}

template<typename ObjectType, typename T, typename sizeType>
EAuthMeEngineReturnCode CallGetArray(long handle, std::vector<T>(ObjectType::*Func)()const, T **ppBuffer, sizeType *pNum)
{
    if (handle == 0 || ppBuffer == NULL || pNum == NULL)
    {
        return eAuthMe_Engine_Failed;
    }

    try
    {
        auto pObj = reinterpret_cast<ObjectType*>(handle);
        auto vec = (pObj->*Func)();

        *ppBuffer = static_cast<T*>(malloc(vec.size() * sizeof(T)));
        *pNum = static_cast<sizeType>(vec.size());
        memcpy(*ppBuffer, vec.data(), vec.size() * sizeof(T));

        return eAuthMe_Engine_Success;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
}

template<typename ServiceType, typename ServiceResult>
EAuthMeEngineReturnCode ServiceRun(long handle, const AuthMeImage* pImage, ServiceResult* pResult)
{
    CheckParamsNoneZero(handle, pImage, pResult);

    try
    {
        auto pService = reinterpret_cast<ServiceType*>(handle);
        auto inputImage = ToCv_BGR(*pImage);
        *pResult = pService->Run(inputImage);

        return eAuthMe_Engine_Success;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
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
        *ppVersion = (AuthMeModelVersion*)malloc(sizeof(AuthMeModelVersion) * vecVersion.size());
        memcpy(*ppVersion, vecVersion.data(), vecVersion.size() * sizeof(AuthMeModelVersion));

        return eAuthMe_Engine_Success;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return eAuthMe_Engine_Failed;
}

template<class ServiceType>
AuthMeEngineDebugInfoList GetDebugInfo(long handle)
{
    if (handle == 0)
    {
        return {};
    }

    try
    {
        auto pObj = reinterpret_cast<ServiceType*>(handle);
        auto &vecDbgInfo = pObj->GetDeBugInfo();

        AuthMeEngineDebugInfoList infoList;
        infoList.len = vecDbgInfo.size();
        infoList.vecDbgInfo = &vecDbgInfo[0];
        return infoList;
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return {};
}

template<class ServiceType>
const char* GetJsonReport(long handle)
{
    if (handle == 0)
    {
        return NULL;
    }

    try
    {
        auto pObj = reinterpret_cast<ServiceType*>(handle);
        const auto& strJson = pObj->GetJsonReport();
        return strJson.c_str();
    }
    catch (const std::exception& e)
    {
        DBG_CERR << e.what() << '\n';
    }

    return NULL;
}


template<class ServiceType>
EAuthMeEngineReturnCode GetDebugImage(long handle, AuthMeImage* pImage)
{
    if (handle == 0 || pImage == NULL)
    {
        return eAuthMe_Engine_Failed;
    }

    auto pService = reinterpret_cast<ServiceType*>(handle);
    auto inputImage = ToCv_BGR(*pImage);
    return pService->GetDebugImage(inputImage);
}

}
