#include "Sandbox2D.h"

#include <imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0)
{
}

void Sandbox2D::OnAttach()
{    
    
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Legacy::Timestep ts)
{
    //OnUpdate
    m_CameraController.OnUpdate(ts);

    //Render
    Legacy::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Legacy::RenderCommand::Clear();

    // m_Camera.SetPosition({0.5f, 0.5f, 0.0f});

    Legacy::Renderer2D::BeginScene(m_CameraController.GetCamera());
    
    
    Legacy::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Legacy::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Legacy::Renderer2D::EndScene();

    //TODO: Add these functions - Shader::SetMat4, Shader::SetFLoat4
    // std::dynamic_pointer_cast<Legacy::OpenGLShader>(m_RectShader)->Bind();
    // std::dynamic_pointer_cast<Legacy::OpenGLShader>(m_RectShader)->UploadUniformFloat4("u_Color", m_SquareColor);
     

    Legacy::Renderer2D::EndScene();
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
