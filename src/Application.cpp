#include "lg_pch.h"
#include "Application.h"
#include "log.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Input.h"
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
        m_ImGuiLayer = new ImGuiLayer;
        PushLayer(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);


        float vertices[]={
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        

        uint32_t indices[]= {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

        std::string vertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Position;
            void main()
            {
                gl_Position = vec4(a_Position, 1.0f);
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            out vec4 color;
            void main()
            {
                color = vec4(0.3f, 0.2f, 0.8f, 1.0f);
            }

        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }
    
    Application::~Application()
    {
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        
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
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();  
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
} // namespace Legacy
