#pragma once


#include <signal.h>
#ifdef HZ_ENABLE_ASSERTS
    #define HZ_ASSERT(x, ...) { if(!(x)) {HZ_ERROR("Assertion failed: {0}", __VA_ARGS__); raise(SIGTRAP);}}
    #define HZ_CORE_ASSERT(x, ...) { if(!(x)) {HZ_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); raise(SIGTRAP);}}
#else
    #define HZ_ASSERT(x, ...)
    #define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
