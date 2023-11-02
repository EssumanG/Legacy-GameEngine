#include "Sandbox2D.h"

#include <imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0)
{
}

void Sandbox2D::OnAttach()
{   
    LG_PROFILE_FUNCTION();
        
    m_Texture = Legacy::Texture2D::Create("/home/essuman/projects/C_or_C++_projects/Game Engine/Leagacy/Sandbox/assets/textures/texture.jpg");
}

void Sandbox2D::OnDetach()
{
    LG_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Legacy::Timestep ts)
{
    LG_PROFILE_FUNCTION();

    //OnUpdate

    m_CameraController.OnUpdate(ts);
   

    //Render
    {
        LG_PROFILE_SCOPE("Renderer Prep");
        Legacy::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Legacy::RenderCommand::Clear();
    }
    // m_Camera.SetPosition({0.5f, 0.5f, 0.0f});

    {
        LG_PROFILE_SCOPE("Renderer Draw");
        Legacy::Renderer2D::BeginScene(m_CameraController.GetCamera());
    
    
        Legacy::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Legacy::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        Legacy::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.2f, 0.8f, 1.0f});
        Legacy::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_Texture);

        Legacy::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnEvent(Legacy::Event &e)
{
     m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
    LG_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Rect Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}
