// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: WindowsInput.h
// Date: 02/10/2019

#pragma once
#include "midori/core/Input.h"

namespace midori {

    class WindowsInput : public Input {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };

}
