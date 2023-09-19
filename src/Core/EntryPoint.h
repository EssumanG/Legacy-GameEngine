#pragma once
#include "Application.h"
#include "log.h"

namespace Legacy{

extern Application* CreateApplication();

}


int main(int argc, char** argv)
{
    Legacy::log::Init();
    LG_CORE_WARN("INITIALIZED LOG!");

    LG_PROFILE_BEGIN_SESSION("Startup", "LegacyProfile-Startup.json");
    auto app = Legacy::CreateApplication();
    LG_PROFILE_END_SESSION();

    LG_PROFILE_BEGIN_SESSION("Runtime", "LegacyProfile-Runtime.json");
    app->Run();
    LG_PROFILE_END_SESSION();

    LG_PROFILE_BEGIN_SESSION("Shutdown", "LegacyProfile-Shutdown.json");
    delete app;
    LG_PROFILE_END_SESSION();
}