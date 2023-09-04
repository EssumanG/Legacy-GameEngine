#include "Sandbox2D.h"

#include <imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include <chrono>

template <typename Fn>
class Timer
{
public:
    Timer(const char* name, Fn&& func)
        : m_Name(name), m_Func(func), m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        if (!m_Stopped)
            Stop();
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        m_Stopped = true;

        auto duration = (end - start) * 0.001f;
        m_Func({m_Name, duration});
    }

private:
    const char* m_Name;
    Fn m_Func;
    std::chrono::time_point<std::chrono::system_clock> m_StartTimepoint;
    bool m_Stopped;
};

 

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult){ m_ProfileResults.push_back(profileResult); })


Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0)
{
}

void Sandbox2D::OnAttach()
{    
    m_Texture = Legacy::Texture2D::Create("/home/essuman/projects/C_or_C++_projects/Game Engine/Leagacy/Sandbox/assets/textures/texture.jpg");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Legacy::Timestep ts)
{
    PROFILE_SCOPE("Sandbox2D::OnUpdate");

    //OnUpdate
    {
        PROFILE_SCOPE("CameraController::OnUpdate");
        m_CameraController.OnUpdate(ts);
    }

    //Render
    {
        PROFILE_SCOPE("Renderer Prep");
        Legacy::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Legacy::RenderCommand::Clear();
    }
    // m_Camera.SetPosition({0.5f, 0.5f, 0.0f});

    {
        PROFILE_SCOPE("Renderer Draw");
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
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Rect Color", glm::value_ptr(m_SquareColor));

    for( auto & result : m_ProfileResults)
    {
        char label[50];
        strcpy(label, " %.3fms ");
        strcat(label, result.Name);

        ImGui::Text(label, result.Time);
    }
    m_ProfileResults.clear();
    ImGui::End();
}
