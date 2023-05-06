#pragma once


#include "../Layer.h"

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
        float m_Time = 0.0f;

        
    };
    
    
} // namespace Hazel
