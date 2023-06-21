#include "lg_pch.h"
#include "Application.h"
#include "log.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Input.h"

#include "Core/Timestep.h"

#include "Renderer/Renderer.h"
namespace Legacy
{
    
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

   
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        LG_CORE_ASSERT(!s_Instance, "Application Already exists!")
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        m_Window->SetVSync(false);

        Renderer::Init();
        m_ImGuiLayer = new ImGuiLayer;

        PushLayer(m_ImGuiLayer);

    }
    
    Application::~Application()
    {
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(OnWindowResize));
        
        // LG_CORE_TRACE("{0}",e.ToString());
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

            float time = glfwGetTime();
            Timestep ts = time - m_LastFrameTime;
            m_LastFrameTime = time;
            if(!m_Minimized)
            {
                for (Layer* layer : m_LayerStack)
                {
                    layer->OnUpdate(ts);  
                }     
            }  
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();  
            m_ImGuiLayer->End();;

            m_Window->OnUpdate();

        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Runnig = false;
        return true;
    }
    bool Application::OnWindowResize(WindowResizedEvent &e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());
        return false;
    }
} // namespace Legacy
