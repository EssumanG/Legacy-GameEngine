#pragma once
#include "../lg_pch.h"

#include "Core.h"
#include "../Events/Event.h"

namespace Legacy 
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string title = "Legacy Engine", unsigned int width = 1280,
                    unsigned int height = 720)
            :Title(title), Width(width), Height(height)
            {
            }
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window Attributes
        virtual void SetEventCallback( const EventCallbackFn& EvenCallbackFn) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;
        virtual void* GetNativeWindow() const = 0;


        static Window* Create(const WindowProps& props = WindowProps());

    };
}