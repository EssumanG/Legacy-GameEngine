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
    int a = 5;
    LG_INFO("HELLO! Var ={0}", a);
    auto app = Legacy::CreateApplication();
    app->Run();
    delete app;
}