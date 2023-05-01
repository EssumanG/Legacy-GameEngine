#pragma once
#include "Application.h"

namespace Hazel{

extern Application* CreateApplication();

}


int main(int argc, char** argv)
{
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}