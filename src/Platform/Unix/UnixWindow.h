#pragma once

#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Hazel
{
    class UnixWindow : public Window
    {
    public:
        UnixWindow(const WindowProps &props);
        virtual ~UnixWindow() override;

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }
        inline virtual void* GetNativeWindow() const override { return m_Window; }

        // Window Attributes
        inline void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool isVSync() const override;

    private:
        virtual void Init(const WindowProps &props);
        virtual void ShutDown();

    private:
        GLFWwindow *m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width;
            unsigned int Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

} // namespace Hazel
