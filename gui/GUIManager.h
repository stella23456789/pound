// Copyright 2025 Pound Emulator Project. All rights reserved.
#pragma once

#include <memory>
#include <vector>
#include <functional>
#include "Window.h"
#include "Panel.h"

namespace Pound::GUI {

class GUIManager {
public:
    GUIManager();
    ~GUIManager();

    bool Initialize(const std::string& title, int width, int height);
    void Shutdown();
    
    void RunFrame();
    bool IsRunning() const { return running && window && !window->ShouldClose(); }
    
    void AddPanel(std::shared_ptr<Panel> panel);
    void RemovePanel(const std::string& name);
    
    // Callback for external systems
    void SetCPUTestCallback(std::function<void()> callback) { cpu_test_callback = callback; }
    
private:
    void BeginFrame();
    void EndFrame();
    void RenderMainMenuBar();
    void ApplyTheme();
    
    std::unique_ptr<Window> window;
    std::vector<std::shared_ptr<Panel>> panels;
    bool running = false;
    bool show_demo_window = false;
    
    // Callbacks
    std::function<void()> cpu_test_callback;
};

} // namespace Pound::GUI