// #include "../src/Test.h"
#include <Legacy/legacy.h>
#include <imgui.h>

class ExampleLayer : public Legacy::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -1.0f, 1.0f)
    {

        m_VertexArray.reset(Legacy::VertexArray::Create());

        float vertices[]={
            -0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.2f, 1.0,
             0.5f, -0.5f, 0.0f, 0.3f, 0.4f, 0.8f, 1.0,
             0.0f,  0.5f, 0.0f, 0.4f, 0.6f, 0.7f, 1.0,
        };


        std::shared_ptr<Legacy::VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(Legacy::VertexBuffer::Create(vertices, sizeof(vertices)));
        Legacy::BufferLayout layout =
        {
            {Legacy::ShaderDataType::Float3, "a_Position"},
            {Legacy::ShaderDataType::Float4, "a_Color"},
        };
        
        m_VertexBuffer->SetLayout(layout); 
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);        

        uint32_t indices[]= {0, 1, 2};
        std::shared_ptr<Legacy::IndexBuffer> m_IndexBuffer; 
        m_IndexBuffer.reset(Legacy::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);





        std::string vertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjectionMatrix;
            out vec4 v_Color;
            void main()
            {
                gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0f);
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

        m_Shader.reset(new Legacy::Shader(vertexSrc, fragmentSrc));
        


        m_RectVertexArray.reset(Legacy::VertexArray::Create());
        float Rectvertices[]={
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
        };


        std::shared_ptr<Legacy::VertexBuffer> m_RectVertexBuffer;
        m_RectVertexBuffer.reset(Legacy::VertexBuffer::Create(Rectvertices, sizeof(Rectvertices)));
        m_RectVertexBuffer->SetLayout({
            {Legacy::ShaderDataType::Float3, "a_Position"}
        });

        m_RectVertexArray->AddVertexBuffer(m_RectVertexBuffer);         
        uint32_t RectIndices[]= {0, 1, 2, 0, 2, 3};
        std::shared_ptr<Legacy::IndexBuffer> m_RectIndexBuffer; 
        m_RectIndexBuffer.reset(Legacy::IndexBuffer::Create(RectIndices, sizeof(RectIndices)/sizeof(uint32_t)));
        m_RectVertexArray->SetIndexBuffer(m_RectIndexBuffer);


        std::string RectvertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjectionMatrix;
            void main()
            {
                gl_Position = u_ViewProjectionMatrix *vec4(a_Position, 1.0f);
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

        m_RectShader.reset(new Legacy::Shader(RectvertexSrc, RectfragmentSrc));
    }

    void OnUpdate(Legacy::Timestep ts) override
    {
        float time = ts.GetTime();
        if (Legacy::Input::isKeyPressed(LG_KEY_LEFT))
             m_CameraPosition.x -= m_CameraMoveSpeed * time;
        else if(Legacy::Input::isKeyPressed(LG_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * time;
        if(Legacy::Input::isKeyPressed(LG_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * time;
        else if(Legacy::Input::isKeyPressed(LG_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * time;

        if(Legacy::Input::isKeyPressed(LG_KEY_A))
            m_CameraRotation += m_CameraRatationSpeed * time;
        if(Legacy::Input::isKeyPressed(LG_KEY_D))
            m_CameraRotation -= m_CameraRatationSpeed * time;

        

        Legacy::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
        Legacy::RenderCommand::Clear();
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
        // m_Camera.SetPosition({0.5f, 0.5f, 0.0f});

        Legacy::Renderer::BeginScene(m_Camera);

        Legacy::Renderer::Submit(m_RectShader, m_RectVertexArray);

        Legacy::Renderer::Submit(m_Shader, m_VertexArray);

        Legacy::Renderer::EndScene();

    }
    virtual void OnImGuiRender() override
    {
    }

    void OnEvent(Legacy::Event& event) override
    {
    }

private:
        std::shared_ptr<Legacy::Shader> m_Shader;
        std::shared_ptr<Legacy::VertexArray> m_VertexArray;

        std::shared_ptr<Legacy::Shader> m_RectShader;
        std::shared_ptr<Legacy::VertexArray> m_RectVertexArray;
        Legacy::OrthographicCamera m_Camera;
        glm::vec3 m_CameraPosition;
        float m_CameraMoveSpeed = 1.0;

        float m_CameraRotation;
        float m_CameraRatationSpeed = 100;
};
class Sandbox : public Legacy::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {
    }


};

Legacy::Application* Legacy::CreateApplication()
{
    return new Sandbox();
}


