#pragma once

#include "../Panel.h"
#include "ARM/cpu.h"
#include <functional>
#include <array>
#include <cstdint>

namespace Pound::GUI
{
    struct CPUState
    {
        std::array<uint64_t, 32> registers{};
        uint64_t pc = 0;
        uint32_t flags = 0;
    };

    class CPUPanel : public Panel
    {
    public:
        CPUPanel();
        void Render() override;
        void SetCPUTestCallback(std::function<void()> callback);
        void UpdateState(const CPU& cpu);

    private:
        CPUState cpu_state;
        bool show_test_result = false;
        std::function<void()> cpu_test_callback;
    };
}