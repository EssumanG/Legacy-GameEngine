#pragma once
#include "Core/Input.h"

namespace Legacy 
{
    class UnixInput : public Input
    {
    protected:
        virtual bool isKeyPressImpl(int keycode) override;
        virtual bool isMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePosImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}