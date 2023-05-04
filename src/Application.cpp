#include "hz_pch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "log.h"

namespace Hazel
{
    Application::Application() 
    {
    }
    
    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizedEvent wr(1234,780);
        HZ_TRACE(wr.ToString().c_str());
        while(true);
    }
} // namespace Hazel
