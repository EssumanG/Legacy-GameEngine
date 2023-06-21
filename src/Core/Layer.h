#pragma once

#include "../lg_pch.h"
#include "Core.h"
#include "../Events/Event.h"

#include "Timestep.h"


namespace Legacy
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnEvent(Event& e) {};
        virtual void OnImGuiRender(){};

        inline const std::string& GetName() { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
} // namespace Legacy
