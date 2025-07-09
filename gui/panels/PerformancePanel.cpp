// Copyright 2025 Pound Emulator Project. All rights reserved.

#include "PerformancePanel.h"
#include <algorithm>

namespace Pound::GUI
{

    PerformancePanel::PerformancePanel() : Panel("Performance")
    {
        last_update = std::chrono::steady_clock::now();
    }

    void PerformancePanel::Render()
    {
        if (!ImGui::Begin(name.c_str(), &visible))
        {
            ImGui::End();
            return;
        }

        Update();

        // Performance metrics
        ImGui::Text("FPS: %.1f", current_data.fps);
        ImGui::Text("Frame Time: %.2f ms", current_data.frame_time);
        ImGui::Separator();

        // FPS Graph
        if (!fps_history.empty())
        {
            float fps_array[HISTORY_SIZE];
            std::copy(fps_history.begin(), fps_history.end(), fps_array);

            ImGui::Text("FPS History:");
            ImGui::PlotLines("##FPS", fps_array, (int)fps_history.size(), 0, nullptr,
                             0.0f, 144.0f, ImVec2(0, 80));
        }

        // Frame Time Graph
        if (!frame_time_history.empty())
        {
            float frame_time_array[HISTORY_SIZE];
            std::copy(frame_time_history.begin(), frame_time_history.end(), frame_time_array);

            ImGui::Text("Frame Time History (ms):");
            ImGui::PlotLines("##FrameTime", frame_time_array, (int)frame_time_history.size(), 0, nullptr,
                             0.0f, 33.33f, ImVec2(0, 80));
        }

        ImGui::Separator();

        // System info (placeholder)
        ImGui::Text("CPU Usage: %.1f%%", current_data.cpu_usage);
        ImGui::Text("Memory Usage: %.1f MB", current_data.memory_usage);

        // Emulation stats
        ImGui::Separator();
        ImGui::Text("Emulation Statistics:");
        ImGui::Text("Instructions/sec: N/A");
        ImGui::Text("JIT Cache Usage: N/A");

        ImGui::End();
    }

    void PerformancePanel::Update()
    {
        frame_count++;

        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update);

        if (duration.count() >= 100)
        { // Update every 100ms
            current_data.fps = frame_count * 1000.0f / duration.count();
            current_data.frame_time = duration.count() / (float)frame_count;

            fps_history.push_back(current_data.fps);
            frame_time_history.push_back(current_data.frame_time);

            // Keep history size limited
            while (fps_history.size() > HISTORY_SIZE)
            {
                fps_history.pop_front();
            }
            while (frame_time_history.size() > HISTORY_SIZE)
            {
                frame_time_history.pop_front();
            }

            frame_count = 0;
            last_update = now;

            // TODO: Get actual CPU and memory usage
            current_data.cpu_usage = 0.0f;
            current_data.memory_usage = 0.0f;
        }
    }

} // namespace Pound::GUI