// Copyright 2025 Pound Emulator Project. All rights reserved.

#include <thread>

#include "Base/Logging/Backend.h"

#include <SDL3/SDL.h>

#include "ARM/cpu.h"
#include "Base/Config.h"
#include "JIT/jit.h"

SDL_Window *Window{};
SDL_Event windowEvent;

void initSDL3() {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_ERROR(Render, "Error while creating SDL3 Context!");
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Pound Emulator");
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, Config::windowWidth());
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, Config::windowHeight());
    // For a new Vulkan support, don't forget to change 'SDL_WINDOW_OPENGL' by 'SDL_WINDOW_VULKAN'.
    SDL_SetNumberProperty(props, "flags", SDL_WINDOW_OPENGL);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);
    Window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);

    SDL_SetWindowMinimumSize(Window, 640, 480);
}

int main() {

    Base::Log::Initialize();
    Base::Log::Start();

    const auto config_dir = Base::FS::GetUserPath(Base::FS::PathType::BinaryDir);
    Config::Load(config_dir / "config.toml");

    initSDL3();

    CPU cpu;
    cpu.pc = 0;

    // Simple ARMv8 program in memory (MOVZ X0, #5; ADD X0, X0, #3; RET)
    // These are placeholders; real encoding will be parsed later
    cpu.write_byte(0, 0x05); // MOVZ placeholder
    cpu.write_byte(4, 0x03); // ADD placeholder
    cpu.write_byte(8, 0xFF); // RET placeholder

    LOG_INFO(ARM, "{}", cpu.read_byte(0));

    JIT jit;
    jit.translate_and_run(cpu);

    cpu.print_debug_information();

    LOG_INFO(ARM, "X0 = {}", cpu.x(0));

    bool rendering = true;

    while (rendering) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        // Process events.
        while (SDL_PollEvent(&windowEvent)) {
            switch (windowEvent.type) {
                case SDL_EVENT_QUIT:
                SDL_DestroyWindow(Window);
                SDL_Quit();
                rendering = false;
            break;
            default:
            break;
            }
        }
    }

    return 0;
}
