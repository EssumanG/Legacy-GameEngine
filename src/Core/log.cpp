#include "lg_pch.h"
#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Legacy {

        std::shared_ptr<spdlog::logger> log::s_CoreLogger;
        std::shared_ptr<spdlog::logger> log::s_ClientLogger;

    void log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

}
