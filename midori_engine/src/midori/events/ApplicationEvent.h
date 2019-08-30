#pragma once

#include "midori/events/Event.h"

namespace Midori {

    class MIDORI_API WindowResizeEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        inline unsigned int GetWidth() const { return m_Width; }
        inline unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

    private:
        unsigned int m_Width, m_Height;
    };

    class MIDORI_API WindowCloseEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

        WindowCloseEvent() {}
    };

    class MIDORI_API AppTickEvent : public Event {
    public:
        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

        AppTickEvent() {}
    };

    class MIDORI_API AppUpdateEvent : public Event {
    public:
        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

        AppUpdateEvent() {}
    };

    class MIDORI_API AppRenderEvent : public Event {
    public:
        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

        AppRenderEvent() {}
    };

}
