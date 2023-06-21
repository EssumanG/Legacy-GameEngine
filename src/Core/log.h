#pragma once

#include "spdlog/spdlog.h"
// #include "spdlog/fmt/ostr.h"


namespace Legacy {

    class log
    {
    public:
       static void Init();

       inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
       inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
    
}

//Core log macros
#define LG_CORE_TRACE(...)      ::Legacy::log::GetCoreLogger()->trace(__VA_ARGS__)
#define LG_CORE_INFO(...)       ::Legacy::log::GetCoreLogger()->info (__VA_ARGS__)
#define LG_CORE_WARN(...)       ::Legacy::log::GetCoreLogger()->warn(__VA_ARGS__)
#define LG_CORE_ERROR(...)      ::Legacy::log::GetCoreLogger()->error(__VA_ARGS__)
#define LG_CORE_FATAL(...)      ::Legacy::log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define LG_TRACE(...)      ::Legacy::log::GetCoreLogger()->trace(__VA_ARGS__)
#define LG_INFO(...)       ::Legacy::log::GetCoreLogger()->info (__VA_ARGS__)
#define LG_WARN(...)       ::Legacy::log::GetCoreLogger()->warn(__VA_ARGS__)
#define LG_ERROR(...)      ::Legacy::log::GetCoreLogger()->error(__VA_ARGS__)
#define LG_FATAL(...)      ::Legacy::log::GetCoreLogger()->fatal(__VA_ARGS__)