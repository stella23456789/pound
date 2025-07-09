// Copyright 2025 Pound Emulator Project. All rights reserved.

#include "ConsolePanel.h"
#include "../Colors.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace Pound::GUI
{

    ConsolePanel::ConsolePanel() : Panel("Console") {}

    void ConsolePanel::Render()
    {
        if (!ImGui::Begin(name.c_str(), &visible))
        {
            ImGui::End();
            return;
        }

        // Options
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &auto_scroll);
            ImGui::Checkbox("Show timestamps", &show_timestamps);
            ImGui::EndPopup();
        }

        // Buttons
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        if (ImGui::Button("Clear"))
            Clear();
        ImGui::SameLine();
        ImGui::Text("Log entries: %zu", log_buffer.size());

        ImGui::Separator();

        // Log display
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        for (const auto &entry : log_buffer)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, entry.color);
            ImGui::TextUnformatted(entry.text.c_str());
            ImGui::PopStyleColor();
        }

        if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::PopStyleVar();
        ImGui::EndChild();

        ImGui::End();
    }

    void ConsolePanel::AddLog(const std::string &text)
    {
        std::string final_text = text;

        if (show_timestamps)
        {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss;
            ss << "[" << std::put_time(std::localtime(&time_t), "%H:%M:%S") << "] ";
            final_text = ss.str() + text;
        }

        log_buffer.push_back({final_text, GetLogColor(text)});

        // Keep buffer size limited
        while (log_buffer.size() > MAX_LOG_ENTRIES)
        {
            log_buffer.pop_front();
        }
    }

    void ConsolePanel::Clear()
    {
        log_buffer.clear();
    }

    ImVec4 ConsolePanel::GetLogColor(const std::string &text) const
    {
        if (text.find("[ERROR]") != std::string::npos)
        {
            return Colors::Error;
        }
        else if (text.find("[WARN]") != std::string::npos)
        {
            return Colors::Warning;
        }
        else if (text.find("[INFO]") != std::string::npos)
        {
            return Colors::Info;
        }
        else if (text.find("[DEBUG]") != std::string::npos)
        {
            return Colors::TextDisabled;
        }
        return Colors::Text;
    }
}