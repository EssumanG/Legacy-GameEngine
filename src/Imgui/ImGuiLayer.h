#pragma once


#include "../Layer.h"

#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"

namespace Hazel 
{

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        virtual ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& e);
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
        bool OnMouseScrolledEvent(MouseScrolledEvent& event);
        bool OnMouseMovedEvent(MouseMovedEvent& event);

        bool OnKeyPressedEvent(KeyPressedEvent& event);
        bool OnKeyReleasedEvent(KeyReleasedEvent& event);
        bool OnKeyTypedEvent(KeyTypedEvent& event);
        bool OnWindowResizedEvent(WindowResizedEvent& event);

    private:
        float m_Time = 0.0f;

        
    };
    
    
} // namespace Hazel
