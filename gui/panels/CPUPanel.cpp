// Copyright 2025 Pound Emulator Project. All rights reserved.

#include "CPUPanel.h"
#include "../Colors.h"
#include <iomanip>
#include <sstream>

namespace Pound::GUI {

CPUPanel::CPUPanel() : Panel("CPU Debug") {}

void CPUPanel::Render() {
    if (!ImGui::Begin(name.c_str(), &visible, ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
        return;
    }
    
    // Control buttons with custom colors
    ImGui::PushStyleColor(ImGuiCol_Button, Colors::WithAlpha(Colors::Primary, 0.40f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Colors::PrimaryHover);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, Colors::PrimaryActive);
    
    if (ImGui::Button("Run CPU Test", ImVec2(120, 0))) {
        if (cpu_test_callback) {
            cpu_test_callback();
            show_test_result = true;
        }
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Step", ImVec2(60, 0))) {
        // TODO: Implement step functionality
    }
    
    ImGui::SameLine();
    
    // Reset button with secondary color
    ImGui::PushStyleColor(ImGuiCol_Button, Colors::WithAlpha(Colors::Secondary, 0.40f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Colors::SecondaryHover);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, Colors::SecondaryActive);
    
    if (ImGui::Button("Reset", ImVec2(60, 0))) {
        // TODO: Implement reset functionality
    }
    
    ImGui::PopStyleColor(6); // Pop all 6 color changes
    
    ImGui::Separator();
    
    // Tabs for different views
    if (ImGui::BeginTabBar("CPUTabBar")) {
        if (ImGui::BeginTabItem("Registers")) {
            // General purpose registers
            ImGui::Text("General Purpose Registers:");
            ImGui::Separator();
            
            if (ImGui::BeginTable("RegisterTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("Register", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 120.0f);
                ImGui::TableSetupColumn("Register", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 120.0f);
                ImGui::TableHeadersRow();
                
                for (int i = 0; i < 16; i++) {
                    ImGui::TableNextRow();
                    
                    // Left column
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("X%d", i);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("0x%016llX", cpu_state.registers[i]);
                    
                    // Right column
                    if (i + 16 < 32) {
                        ImGui::TableSetColumnIndex(2);
                        ImGui::Text("X%d", i + 16);
                        ImGui::TableSetColumnIndex(3);
                        ImGui::Text("0x%016llX", cpu_state.registers[i + 16]);
                    }
                }
                
                ImGui::EndTable();
            }
            
            ImGui::Spacing();
            ImGui::Text("Program Counter: 0x%016llX", cpu_state.pc);
            ImGui::Text("Flags: 0x%08X", cpu_state.flags);
            
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Memory")) {
            static char addr_input[17] = "0000000000000000";
            ImGui::Text("Memory Viewer");
            ImGui::Separator();
            
            ImGui::InputText("Address", addr_input, sizeof(addr_input), 
                ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
            
            // TODO: Implement memory viewer
            ImGui::Text("Memory viewer will be implemented here");
            
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Disassembly")) {
            ImGui::Text("Disassembly View");
            ImGui::Separator();
            
            // TODO: Implement disassembly view
            ImGui::Text("Disassembly will be shown here");
            
            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }
    
    // Test result popup
    if (show_test_result) {
        ImGui::OpenPopup("CPU Test Result");
    }
    
    if (ImGui::BeginPopupModal("CPU Test Result", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("The CPU test has been executed successfully!");
        ImGui::Text("Check the console for detailed output.");
        ImGui::Separator();
        ImGui::Text("Note: Pound is still in pre-alpha state.");
        
        ImGui::Spacing();
        
        if (ImGui::Button("OK", ImVec2(120, 0))) {
            show_test_result = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
    
    ImGui::End();
}

} // namespace Pound::GUI