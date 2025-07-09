// In gui/panels/CPUPanel.cpp

#include "CPUPanel.h"
#include "../Colors.h"
#include <imgui.h>
#include <cinttypes>

namespace Pound::GUI
{
    CPUPanel::CPUPanel() : Panel("CPU Debug") {}

    void CPUPanel::UpdateState(const CPU& cpu)
    {
        cpu.get_state(cpu_state.registers.data(), cpu_state.pc);
    }

    void CPUPanel::SetCPUTestCallback(std::function<void()> callback)
    {
        cpu_test_callback = std::move(callback);
    }
    
    void CPUPanel::Render()
    {
        if (!visible) {
            return;
        }
        if (!ImGui::Begin(name.c_str(), &visible, ImGuiWindowFlags_NoCollapse))
        {
            ImGui::End();
            return;
        }

        ImGui::PushStyleColor(ImGuiCol_Button, Colors::WithAlpha(Colors::Primary, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Colors::PrimaryHover);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, Colors::PrimaryActive);
        if (ImGui::Button("Run CPU Test", ImVec2(120, 0)))
        {
            if (cpu_test_callback) {
                cpu_test_callback();
                show_test_result = true;
            }
        }
        ImGui::PopStyleColor(3);
        ImGui::Separator();
        if (ImGui::BeginTabBar("CPUTabBar"))
        {
            if (ImGui::BeginTabItem("Registers"))
            {
                ImGui::Text("General Purpose Registers:");
                ImGui::Separator();
                if (ImGui::BeginTable("RegisterTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("Register"); ImGui::TableSetupColumn("Value");
                    ImGui::TableSetupColumn("Register"); ImGui::TableSetupColumn("Value");
                    ImGui::TableHeadersRow();

                    for (int i = 0; i < 16; i++)
                    {
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0); ImGui::Text("X%d", i);
                        ImGui::TableSetColumnIndex(1); ImGui::Text("0x%016" PRIX64, cpu_state.registers[i]);
    
                        if (i + 16 < 31)
                        {
                            ImGui::TableSetColumnIndex(2); ImGui::Text("X%d", i + 16);
                            ImGui::TableSetColumnIndex(3); ImGui::Text("0x%016" PRIX64, cpu_state.registers[i + 16]);
                        }
                    }
                    ImGui::EndTable();
                }

                ImGui::Spacing();
                ImGui::Text("Program Counter: 0x%016" PRIX64, cpu_state.pc);
                ImGui::Text("Flags (PState):  0x%08X", cpu_state.flags); 
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Memory")) { /*...*/ ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Disassembly")) { /*...*/ ImGui::EndTabItem(); }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }

} // namespace Pound::GUI