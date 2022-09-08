#pragma once
#include <chrono>

namespace AuthMe
{

class CServiceBase
{
    public:
        CServiceBase();
        virtual ~CServiceBase();

        void SetTimeoutTime(int iSec);
        bool Start();
        bool Stop();
        bool IsRunning() const;
        bool IsAlreadyPass() const;
        void SetPass();
        void SetFail();
        bool IsFail() const;
        bool IsTimeout() const;

    private:
        bool m_bIsRunning = false;
        bool m_bPass = false;
        bool m_bFail = false;
        int m_iTimeoutSec = 0;
        std::chrono::time_point<std::chrono::system_clock> m_startTime;
};

}
