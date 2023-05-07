#pragma once


namespace Legacy
{
    
    class Input
    {
    public:
        inline static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressImpl(keycode); }
        inline static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePos() {return s_Instance->GetMousePosImpl(); }
        inline static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }    
    protected:
        virtual bool isKeyPressImpl(int keycode) = 0;
        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePosImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:
        static Input* s_Instance;
    
    };
} // namespace Legacy
