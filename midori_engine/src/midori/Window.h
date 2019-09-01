#pragma once
#include "mdpch.h"
#include "midori/Core.h"
#include "midori/events/Event.h"

namespace Midori {
    
    struct WindowProperties {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProperties(const std::string& title = "Midori Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class MIDORI_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual inline int GetWindowWidth() const = 0;
        virtual inline int GetWindowHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        virtual void SetVSync(bool enableVSync) = 0;
        virtual bool IsVSyncEnabled() const = 0;

        static Window* Create(const WindowProperties& props = WindowProperties());
    };

}
