#include "lg_pch.h"
#include "Application.h"
#include "log.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Input.h"
namespace Legacy
{
    
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
        }

        LG_CORE_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }
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
            -0.5f, -0.5f, 0.0f, 0.4f, 0.3f, 0.5f, 1.0,
             0.5f, -0.5f, 0.0f, 0.5f, 0.4f, 0.3f, 1.0,
             0.0f,  0.5f, 0.0f, 0.3f, 0.5f, 0.4f, 1.0,
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout =
        {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };

        m_VertexBuffer->SetLayout(layout);

        uint32_t index = 0;
        for (auto& element: m_VertexBuffer->GetLayout() )
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, 
                element.GetComponentCount(), 
                ShaderDataTypeToOpenGLDataType(element.Type), 
                element.Normalized ? GL_TRUE : GL_FALSE, 
                m_VertexBuffer->GetLayout().GetStride(), 
                (const void *)element.Offset);
            index++;
        }


        

        uint32_t indices[]= {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

        std::string vertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec4 a_Color;

            out vec4 v_Color;
            void main()
            {
                gl_Position = vec4(a_Position, 1.0f);
                v_Color = a_Color;
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core
            in vec4 v_Color;
            out vec4 color;
            void main()
            {
                // color = vec4(0.3f, 0.2f, 0.8f, 1.0f);
                color = v_Color;
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
