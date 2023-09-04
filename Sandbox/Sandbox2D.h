#pragma once
#include <Legacy/legacy.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Sandbox2D : public Legacy::Layer
{
public:
    Sandbox2D(/* args */);
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Legacy::Timestep ts) override;
    virtual void OnEvent(Legacy::Event& e) override;
    virtual void OnImGuiRender() override;

private:
    Legacy::OrthographicCameraController m_CameraController;

    Legacy::Ref<Legacy::VertexArray> m_RectVertexArray;

    Legacy::Ref<Legacy::Shader> m_RectShader;
    Legacy::Ref<Legacy::Texture2D> m_Texture;

    struct ProfileResult
    {
        const char* Name;
        float Time;
    };

    std::vector<ProfileResult> m_ProfileResults;
    glm::vec4 m_SquareColor = { 0.3f, 0.4f, 0.9f, 1.0f };
};
