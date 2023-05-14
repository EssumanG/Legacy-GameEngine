#pragma once
// #include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Imgui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"
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
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        std::shared_ptr<Shader> m_RectShader;
        std::shared_ptr<VertexArray> m_RectVertexArray;
        OrthographicCamera m_Camera;
        
    private:
        static Application* s_Instance;
    };
    
   
    
} // namespace Legacy
