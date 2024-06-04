#pragma once
#include "Engine/Core/Input.h"

class CWindowsInput final : public CInput 
{
protected:
    virtual bool KeyPressedImpl(int keyCode) override;
    virtual bool MouseButtonPressedImpl(int keyCode) override;

    virtual float GetMouseXImpl() override;
    virtual float GetMouseYImpl() override;

    virtual std::pair<float, float> GetMousePositionImpl() override;
};