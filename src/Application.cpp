#include "hz_pch.h"
#include "Application.h"
#include "log.h"

#include "GLFW/glfw3.h"

namespace Hazel
{
    
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application::Application() 
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }
    
    Application::~Application()
    {
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        
        HZ_CORE_TRACE("{0}",e.ToString());
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.is_Handled())
                break;
            
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushLayer(overlay);
    }

    void Application::Run()
    {
        
        while(m_Runnig)
        {
            m_Window->OnUpdate();
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();   
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Runnig = false;
        return true;
    }
} // namespace Hazel
