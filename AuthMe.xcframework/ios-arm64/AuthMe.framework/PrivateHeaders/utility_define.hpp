#pragma once
#include <chrono>
#include <vector>

#define PERF_BEG(tag) auto t_##tag##_beg = std::chrono::high_resolution_clock::now();
#define PERF_END(tag) auto t_##tag##_end = std::chrono::high_resolution_clock::now();
#define DURATION_MS(tag) (std::chrono::duration_cast<std::chrono::microseconds>(t_##tag##_end - t_##tag##_beg).count() / 1000.0)
#define DURATION_US(tag) std::chrono::duration_cast<std::chrono::microseconds>(t_##tag##_end - t_##tag##_beg).count()

#define TimeTest(doSomthing, count, title) \
do \
{ \
    PERF_BEG(t) \
    for (int i = 0; i < count; i++) \
    { \
        doSomthing; \
    } \
    PERF_END(t) \
    std::cout << title << ": run " << count << " times, avg " << static_cast<double>(DURATION_MS(t)) / static_cast<double>(count) << " ms" << std::endl; \
} while (0)

#define SafeDelete(p) {if (p!=nullptr) delete p; p = nullptr;} while(0)
#define SafeDeleteArray(p) {if (p!=nullptr) delete[] p; p = nullptr;} while(0)

#ifdef _AUTHME_DEBUG_
#define DBG_OUT std::cout
#define DBG_CERR std::cerr
#else
#define DBG_OUT if(0) std::cout
#define DBG_CERR if(0) std::cerr
#endif