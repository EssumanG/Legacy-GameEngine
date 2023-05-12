#include "lg_pch.h"
#include "Application.h"
#include "log.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Input.h"

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
        m_ImGuiLayer = new ImGuiLayer;
        PushLayer(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[]={
            -0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.2f, 1.0,
             0.5f, -0.5f, 0.0f, 0.3f, 0.4f, 0.8f, 1.0,
             0.0f,  0.5f, 0.0f, 0.4f, 0.6f, 0.7f, 1.0,
        };


        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout =
        {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };
        
        m_VertexBuffer->SetLayout(layout); 
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);        

        uint32_t indices[]= {0, 1, 2};
        std::shared_ptr<IndexBuffer> m_IndexBuffer; 
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);





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
        


        m_RectVertexArray.reset(VertexArray::Create());
        float Rectvertices[]={
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
        };


        std::shared_ptr<VertexBuffer> m_RectVertexBuffer;
        m_RectVertexBuffer.reset(VertexBuffer::Create(Rectvertices, sizeof(Rectvertices)));
        m_RectVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"}
        });

        m_RectVertexArray->AddVertexBuffer(m_RectVertexBuffer);         
        uint32_t RectIndices[]= {0, 1, 2, 0, 2, 3};
        std::shared_ptr<IndexBuffer> m_RectIndexBuffer; 
        m_RectIndexBuffer.reset(IndexBuffer::Create(RectIndices, sizeof(RectIndices)/sizeof(uint32_t)));
        m_RectVertexArray->SetIndexBuffer(m_RectIndexBuffer);


        std::string RectvertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Position;
            void main()
            {
                gl_Position = vec4(a_Position, 1.0f);
            }

        )";

        std::string RectfragmentSrc = R"(
            #version 330 core
            out vec4 color;
            void main()
            {
                color = vec4(0.2f, 0.5f, 0.5f, 1.0f);

            }

        )";

        m_RectShader.reset(new Shader(RectvertexSrc, RectfragmentSrc));
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
            RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_RectShader->Bind();
            Renderer::Submit(m_RectVertexArray);

            m_Shader->Bind();
            Renderer::Submit(m_VertexArray);

            Renderer::EndScene();


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
