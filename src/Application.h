#pragma once
// #include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Imgui/ImGuiLayer.h"
#include "LayerStack.h"
namespace Legacy
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *m_Window; }
        inline static Application& Get() { return *s_Instance;}
    private:
        bool OnWindowClose(WindowCloseEvent& e);


    private:
        std::unique_ptr<Window> m_Window;
        bool m_Runnig = true;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
    private:
        static Application* s_Instance;
    };
    
   
    
} // namespace Legacy
