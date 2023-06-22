#include "Sandbox2D.h"

#include <imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0)
{
}

void Sandbox2D::OnAttach()
{    
    m_RectVertexArray = Legacy::VertexArray::Create();
    float Rectvertices[]={
        -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };


    Legacy::Ref<Legacy::VertexBuffer> m_RectVertexBuffer;
    m_RectVertexBuffer = Legacy::VertexBuffer::Create(Rectvertices, sizeof(Rectvertices));
    m_RectVertexBuffer->SetLayout({
        {Legacy::ShaderDataType::Float3, "a_Position"},
    });

    m_RectVertexArray->AddVertexBuffer(m_RectVertexBuffer);         
    uint32_t RectIndices[]= {0, 1, 2, 0, 2, 3};
    Legacy::Ref<Legacy::IndexBuffer> m_RectIndexBuffer; 
    m_RectIndexBuffer = Legacy::IndexBuffer::Create(RectIndices, sizeof(RectIndices)/sizeof(uint32_t));
    m_RectVertexArray->SetIndexBuffer(m_RectIndexBuffer);

    
    m_RectShader = Legacy::Shader::Create("/home/essuman/projects/C_or_C++_projects/Game Engine/Leagacy/Sandbox/assets/shaders/RectColor.glsl");

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Legacy::Timestep ts)
{
    //OnUpdate
    m_CameraController.OnUpdate(ts);

    //Render
    Legacy::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    Legacy::RenderCommand::Clear();

    // m_Camera.SetPosition({0.5f, 0.5f, 0.0f});

    Legacy::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Legacy::OpenGLShader>(m_RectShader)->Bind();
    std::dynamic_pointer_cast<Legacy::OpenGLShader>(m_RectShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    Legacy::Renderer::Submit(m_RectShader, m_RectVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5)));

    Legacy::Renderer::EndScene();

}

void Sandbox2D::OnEvent(Legacy::Event &e)
{
     m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Rect Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}
