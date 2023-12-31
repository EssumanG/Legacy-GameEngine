#pragma once
#include "OrthographicCamera.h"
#include "../Core/Timestep.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"

namespace Legacy
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void setProjection(float left, float right, float bottom, float top);
        void OnUpdate(Timestep ts);
        void OnEvent(Event &e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent &e);
        bool OnWindowResized(WindowResizedEvent &e);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;
        
        bool m_Rotation;
        float m_CameraRotation = 0.0f;
        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraTranslationSpeed = 5.0f;
        float m_CameraRotationSpeed = 180.0f;

    };

}