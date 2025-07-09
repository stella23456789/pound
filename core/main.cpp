// Copyright 2025 Pound Emulator Project. All rights reserved.

#include <thread>
#include <memory>
#include <chrono>

#include "Base/Logging/Backend.h"
#include "Base/Config.h"
#include "ARM/cpu.h"
#include "JIT/jit.h"

#include "gui/GUIManager.h"
#include "gui/panels/ConsolePanel.h"
#include "gui/panels/CPUPanel.h"
#include "gui/panels/PerformancePanel.h"

// CPU test function
void cpuTest() {
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
}

int main() {
    Base::Log::Initialize();
    Base::Log::Start();

    const auto config_dir = Base::FS::GetUserPath(Base::FS::PathType::BinaryDir);
    Config::Load(config_dir / "config.toml");

    // Create GUI manager
    auto gui_manager = std::make_unique<Pound::GUI::GUIManager>();
    
    // Initialize GUI
    if (!gui_manager->Initialize("Pound Emulator", Config::windowWidth(), Config::windowHeight())) {
        LOG_ERROR(Render, "Failed to initialize GUI");
        return -1;
    }

    // Create and add panels
    auto console_panel = std::make_shared<Pound::GUI::ConsolePanel>();
    auto cpu_panel = std::make_shared<Pound::GUI::CPUPanel>();
    auto performance_panel = std::make_shared<Pound::GUI::PerformancePanel>();
    
    gui_manager->AddPanel(console_panel);
    gui_manager->AddPanel(cpu_panel);
    gui_manager->AddPanel(performance_panel);
    
    // Set up callbacks
    auto cpu_test_callback = [console_panel]() {
        console_panel->AddLog("[INFO] Running CPU test...");
        cpuTest();
        console_panel->AddLog("[INFO] CPU test completed. Check terminal for details.");
    };
    
    gui_manager->SetCPUTestCallback(cpu_test_callback);
    cpu_panel->SetCPUTestCallback(cpu_test_callback);
    
    // Add initial console message
    console_panel->AddLog("[INFO] Pound Emulator started");
    console_panel->AddLog("[INFO] Version: Pre-Alpha");
    
    // Main loop
    while (gui_manager->IsRunning()) {
        gui_manager->RunFrame();
        
        // Small delay to prevent excessive CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    // Cleanup
    gui_manager->Shutdown();
    
    return 0;
}