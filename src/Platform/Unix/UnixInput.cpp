#include "lg_pch.h"
#include "UnixInput.h"
#include "GLFW/glfw3.h"
#include "Core/Application.h"


namespace Legacy
{
    Input* Input::s_Instance = new UnixInput;

    bool UnixInput::isKeyPressImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetKey(window, keycode);
        return (state == GLFW_PRESS || state == GLFW_REPEAT);        
    }

    bool UnixInput::isMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetMouseButton(window, button);
        return (state == GLFW_PRESS);
    }

    std::pair<float, float> UnixInput::GetMousePosImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }

    float UnixInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePosImpl();
        return x;
    }


    float UnixInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePosImpl();
        return y;
    }
}