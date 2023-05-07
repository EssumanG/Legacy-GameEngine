#pragma once


#include <signal.h>
#ifdef LG_ENABLE_ASSERTS
    #define LG_ASSERT(x, ...) { if(!(x)) {LG_ERROR("Assertion failed: {0}", __VA_ARGS__); raise(SIGTRAP);}}
    #define LG_CORE_ASSERT(x, ...) { if(!(x)) {LG_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); raise(SIGTRAP);}}
#else
    #define LG_ASSERT(x, ...)
    #define LG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
