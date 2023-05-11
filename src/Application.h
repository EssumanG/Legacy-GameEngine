#pragma once
// #include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Imgui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
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
        unsigned int m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
    private:
        static Application* s_Instance;
    };
    
   
    
} // namespace Legacy
