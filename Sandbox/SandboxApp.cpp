// #include "../src/Test.h"
#include <Legacy/legacy.h>

class ExampleLayer : public Legacy::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        //LG_INFO("ExampleLayer::Update");

        if(Legacy::Input::isKeyPressed(LG_KEY_TAB))
            LG_INFO("Tab key is pressed!");

    }

    void OnEvent(Legacy::Event& event) override
    {
        // LG_TRACE("{0}", event.ToString());
    }
};
class Sandbox : public Legacy::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Legacy::ImGuiLayer());
    }

    ~Sandbox()
    {
    }


};

Legacy::Application* Legacy::CreateApplication()
{
    return new Sandbox();
}


