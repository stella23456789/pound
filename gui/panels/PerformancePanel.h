// Copyright 2025 Pound Emulator Project. All rights reserved.
#pragma once

#include "../Panel.h"
#include <deque>
#include <chrono>

namespace Pound::GUI
{

    class PerformancePanel : public Panel
    {
    public:
        PerformancePanel();

        void Render() override;
        void Update();

    private:
        struct PerformanceData
        {
            float fps = 0.0f;
            float frame_time = 0.0f;
            float cpu_usage = 0.0f;
            float memory_usage = 0.0f;
        };

        PerformanceData current_data;
        std::deque<float> fps_history;
        std::deque<float> frame_time_history;
        static constexpr size_t HISTORY_SIZE = 120;

        std::chrono::steady_clock::time_point last_update;
        int frame_count = 0;
    };

} // namespace Pound::GUI