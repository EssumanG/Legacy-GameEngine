#pragma once
#include "Application.h"
#include "log.h"

namespace Hazel{

extern Application* CreateApplication();

}


int main(int argc, char** argv)
{
    Hazel::log::Init();
    HZ_CORE_WARN("INITIALIZED LOG!");
    int a = 5;
    HZ_INFO("HELLO! Var ={0}", a);
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}