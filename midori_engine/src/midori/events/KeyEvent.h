#pragma once

#include "midori/events/Event.h"

namespace midori {

    class MIDORI_API KeyEvent : public Event {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        inline int GetKeyCode() const { return m_KeyCode; }

    protected:
        KeyEvent(int keycode)
            : m_KeyCode(keycode) {}

        int m_KeyCode;
    };

    class MIDORI_API KeyPressedEvent : public KeyEvent {
    public:
        EVENT_CLASS_TYPE(KeyPressed)

        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

    private:
        int m_RepeatCount;
    };

    class MIDORI_API KeyReleasedEvent : public KeyEvent {
    public:
        EVENT_CLASS_TYPE(KeyReleased)

        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }
    };

}
