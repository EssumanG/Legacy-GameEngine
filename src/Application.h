#pragma once
// #include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"
namespace Hazel
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        bool OnWindowClose(WindowCloseEvent& e);


    private:
        std::unique_ptr<Window> m_Window;
        bool m_Runnig = true;
        LayerStack m_LayerStack;
    };
    
   
    
} // namespace Hazel
