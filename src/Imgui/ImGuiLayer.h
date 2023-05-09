#pragma once


#include "../Layer.h"

#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"

namespace Legacy 
{

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        virtual ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        void Begin();
        void End();

    private:
        float m_Time = 0.0f;

        
    };
    
    
} // namespace Legacy
