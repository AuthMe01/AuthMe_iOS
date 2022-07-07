#pragma once
#include <chrono>

namespace AuthMe
{

class CServiceBase
{
    public:
        CServiceBase();
        virtual ~CServiceBase();

        virtual void SetTimeoutTime(int iSec);
        virtual void Start();
        virtual bool IsAlreadyPass();
        virtual void SetPass();
        virtual void SetFail();
        virtual bool IsFail();
        virtual bool IsTimeout();

    private:
        bool m_bPass = false;
        bool m_bFail = false;
        int m_iTimeoutSec = 0;
        std::chrono::time_point<std::chrono::system_clock> m_startTime;
};

}
