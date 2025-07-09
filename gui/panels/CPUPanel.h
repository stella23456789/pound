// Copyright 2025 Pound Emulator Project. All rights reserved.
#pragma once

#include "../Panel.h"
#include <functional>

namespace Pound::GUI
{

    class CPUPanel : public Panel
    {
    public:
        CPUPanel();

        void Render() override;
        void SetCPUTestCallback(std::function<void()> callback) { cpu_test_callback = callback; }
        void ShowTestResult(bool show = true) { show_test_result = show; }

    private:
        std::function<void()> cpu_test_callback;
        bool show_test_result = false;

        // CPU state display (placeholder for future integration)
        struct CPUState
        {
            uint64_t registers[32] = {0};
            uint64_t pc = 0;
            uint32_t flags = 0;
        } cpu_state;
    };

} // namespace Pound::GUI