#include "hz_pch.h"
#include "Application.h"
#include "log.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Input.h"
namespace Hazel
{
    
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


    Application* Application::s_Instance = nullptr;

    Application::Application() 
    {
        HZ_CORE_ASSERT(!s_Instance, "Application Already exists!")
        s_Instance = this;

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
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Run()
    {
        
        while(m_Runnig)
        {
            glClearColor(0.4f, 0.5f, 0.5f, 1.0f);
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();  

            }
            
            auto[x, y] = Input::GetMousePos();
            HZ_CORE_TRACE("{0} , {1}", x, y);

            m_Window->OnUpdate();

        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Runnig = false;
        return true;
    }
} // namespace Hazel
