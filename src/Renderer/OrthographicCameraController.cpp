#include "lg_pch.h"
#include "Renderer/OrthographicCameraController.h"
#include "src/Core/Input.h"
#include "src/Core/KeyCodes.h"


namespace Legacy
{

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio),
        m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
        m_Rotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        float time = ts.GetTime();
        if (Input::isKeyPressed(LG_KEY_A))
             m_CameraPosition.x -= m_CameraTranslationSpeed * time;
        else if(Input::isKeyPressed(LG_KEY_D))
            m_CameraPosition.x += m_CameraTranslationSpeed * time;
        if(Input::isKeyPressed(LG_KEY_W))
            m_CameraPosition.y += m_CameraTranslationSpeed * time;
        else if(Input::isKeyPressed(LG_KEY_S))
            m_CameraPosition.y -= m_CameraTranslationSpeed * time;

        if(m_Rotation)
        {
            if(Input::isKeyPressed(LG_KEY_Q))
                m_CameraRotation += m_CameraRotationSpeed * time;
            if(Input::isKeyPressed(LG_KEY_E))
                m_CameraRotation -= m_CameraRotationSpeed * time;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);
    }
        

    void OrthographicCameraController::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(LG_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizedEvent>(LG_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizedEvent &e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

} // namespace Legacy
