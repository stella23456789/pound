// Copyright 2025 Pound Emulator Project. All rights reserved.
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <memory>
#include <string>

namespace Pound::GUI
{

    class Window
    {
    public:
        Window();
        ~Window();

        bool Initialize(const std::string &title, int width, int height);
        void Shutdown();

        SDL_Window *GetSDLWindow() const { return window; }
        SDL_GLContext GetGLContext() const { return gl_context; }

        bool ShouldClose() const { return should_close; }
        void SetShouldClose(bool close) { should_close = close; }

        void ProcessEvents();
        void SwapBuffers();

    private:
        SDL_Window *window = nullptr;
        SDL_GLContext gl_context = nullptr;
        bool should_close = false;
    };

} // namespace Pound::GUI