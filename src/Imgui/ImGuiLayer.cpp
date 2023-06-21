#include "lg_pch.h"
#include "Imgui/ImGuiLayer.h"
#include "Core/Application.h"


//Temporary
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
// #include "Platform/Unix/UnixWindow.h"



#include "ImGuiLayer.h"

namespace Legacy
{
    ImGuiLayer::ImGuiLayer()
        :Layer("ImGui Layer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark(); 

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application &app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }


    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        //Rendeing
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }


    }

    void ImGuiLayer::OnImGuiRender()
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }
    /* Implementing Your Own event handling*/
    // void ImGuiLayer::OnEvent(Event &e)
    // {
    //     EventDispatcher dispatcher(e);
    //     dispatcher.Dispatcher<MouseButtonPressedEvent>(LG_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    //     dispatcher.Dispatcher<MouseButtonReleasedEvent>(LG_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    //     dispatcher.Dispatcher<MouseMovedEvent>(LG_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    //     // dispatcher.Dispatcher<MouseScrolledEvent>(LG_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    //     dispatcher.Dispatcher<KeyPressedEvent>(LG_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    //     dispatcher.Dispatcher<KeyTypedEvent>(LG_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
    //     dispatcher.Dispatcher<KeyReleasedEvent>(LG_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    //     dispatcher.Dispatcher<WindowResizedEvent>(LG_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));

    // }

    // bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &event)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //     io.MouseDown[event.GetMouseButton()] = true;
    //     return false;
    // }
    // bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //     io.MouseDown[event.GetMouseButton()] = false;
    //     return false;
        
    // }
    // bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &event)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //     io.MousePos = ImVec2(event.GetX(), event.GetY());
    //     return false;
        
    // }
    // // bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
    // // {
    // //     ImGuiIO& io = ImGui::GetIO();
    // //     io.MouseWheel += event.GetYOffset();
    // //     io.MouseWheelH += event.GetXOffset();

    // //     return false;
    // // }
    // bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &event)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //     io.KeysDown[event.GetKeyCode()] = true;

    //     io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    //     io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    //     io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    //     io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    //     return false;
    // }
    // bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &event)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //     io.KeysDown[event.GetKeyCode()] = false;

    //     return false;
    // }
    // bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &event)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //     int keycode = event.GetKeyCode();
    //     if (keycode > 0 && keycode < 0x1000)
    //         io.AddInputCharacter((unsigned short)keycode);

    //     return false;
    // }
    // bool ImGuiLayer::OnWindowResizedEvent(WindowResizedEvent &event)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //     io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
    //     io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    //     glViewport(0, 0, event.GetWidth(), event.GetHeight());
    //     return false;
    // }
}