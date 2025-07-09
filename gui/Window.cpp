// Copyright 2025 Pound Emulator Project. All rights reserved.

#include "Window.h"
#include "Base/Logging/Log.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

namespace Pound::GUI
{

    Window::Window() = default;

    Window::~Window()
    {
        Shutdown();
    }

    bool Window::Initialize(const std::string &title, int width, int height)
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            LOG_ERROR(Render, "Error while creating SDL3 Context!");
            return false;
        }

        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title.c_str());
        SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
        SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);
        SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
        SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
        SDL_SetNumberProperty(props, "flags", SDL_WINDOW_OPENGL);
        SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
        SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);

        window = SDL_CreateWindowWithProperties(props);
        SDL_DestroyProperties(props);

        if (!window)
        {
            LOG_ERROR(Render, "Failed to create SDL window: {}", SDL_GetError());
            return false;
        }

        SDL_SetWindowMinimumSize(window, 640, 480);

        gl_context = SDL_GL_CreateContext(window);
        if (!gl_context)
        {
            LOG_ERROR(Render, "Failed to create OpenGL context: {}", SDL_GetError());
            return false;
        }

        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1);

        return true;
    }

    void Window::Shutdown()
    {
        if (gl_context)
        {
            SDL_GL_DestroyContext(gl_context);
            gl_context = nullptr;
        }

        if (window)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }

        SDL_Quit();
    }

    void Window::ProcessEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT)
            {
                should_close = true;
            }
        }
    }

    void Window::SwapBuffers()
    {
        SDL_GL_SwapWindow(window);
    }

} // namespace Pound::GUI