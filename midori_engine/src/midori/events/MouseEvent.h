// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: MouseEvent.h
// Date: 10/10/2019

#pragma once

#include "midori/events/Event.h"

namespace midori {

    class MIDORI_API MouseMovedEvent : public Event {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        EVENT_CLASS_TYPE(MouseMoved)

        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        MouseMovedEvent() = delete;

        inline float GetX() const { return m_MouseX; }

        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

    private:
        float m_MouseX, m_MouseY;
    };

    class MIDORI_API MouseScrolledEvent : public Event {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        EVENT_CLASS_TYPE(MouseScrolled)

        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        MouseScrolledEvent() = delete;

        inline float GetXOffset() const { return m_XOffset; }

        inline float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

    private:
        float m_XOffset, m_YOffset;
    };

    class MIDORI_API MouseButtonEvent : public Event {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        inline int GetMouseButton() const { return m_Button; }

    protected:
        MouseButtonEvent(int button)
            : m_Button(button) {}

        int m_Button;
    };

    class MIDORI_API MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        EVENT_CLASS_TYPE(MouseButtonPressed)

        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        MouseButtonPressedEvent() = delete;

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
    };

    class MIDORI_API MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        EVENT_CLASS_TYPE(MouseButtonReleased)

        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        MouseButtonReleasedEvent() = delete;

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }
    };

}
