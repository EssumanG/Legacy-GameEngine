#pragma once
// #include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
namespace Hazel
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent& e);

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Runnig = true;
    };
    
   
    
} // namespace Hazel
