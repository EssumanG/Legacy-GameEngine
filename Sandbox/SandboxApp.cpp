// #include "../src/Test.h"
#include <Legacy/legacy.h>
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/Platform/OpenGL/OpenGLShader.h"

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
            uniform mat4 u_Transform;
            // out vec4 v_Color;
            void main()
            {
                gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0f);
                // v_Color = a_Color;
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core
            in vec4 v_Color;
            out vec4 color;
            void main()
            {
                color = vec4(0.3f, 0.2f, 0.8f, 1.0f);
                // color = v_Color;
            }

        )";

        m_Shader.reset(Legacy::Shader::Create(vertexSrc, fragmentSrc));
        // std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->
        


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
            uniform mat4 u_Transform;
            void main()
            {
                gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0f);
            }

        )";

        std::string RectfragmentSrc = R"(
            #version 330 core
            out vec4 color;
            uniform vec3 u_Color;
            void main()
            {
                color = vec4(u_Color, 1.0f);

            }

        )";

       
        m_RectShader.reset(Legacy::Shader::Create(RectvertexSrc, RectfragmentSrc));
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

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1));

        std::dynamic_pointer_cast<Legacy::OpenGLShader>(m_RectShader)->Bind();
        std::dynamic_pointer_cast<Legacy::OpenGLShader>(m_RectShader)->UploadUniformFloat3("u_Color", m_SquareColor);


        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                glm::vec3 pos(i * 0.17f, j * 0.17f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Legacy::Renderer::Submit(m_RectShader, m_RectVertexArray, transform);
            }
        }



        Legacy::Renderer::Submit(m_Shader, m_VertexArray);

        Legacy::Renderer::EndScene();

    }
    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Rect Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
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

        float m_CameraRotation = 0.0f;
        float m_CameraRatationSpeed = 100;

        glm::vec3 m_SquareColor = { 0.5f, 0.6f, 0.9f };

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


