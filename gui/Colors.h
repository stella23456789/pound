// Copyright 2025 Pound Emulator Project. All rights reserved.
#pragma once

#include <imgui.h>

namespace Pound::GUI {

class Colors {
public:
    // Primary colors
    static constexpr ImVec4 Primary = ImVec4(0.0f, 0.765f, 0.890f, 1.0f);         // #00c3e3
    static constexpr ImVec4 PrimaryHover = ImVec4(0.0f, 0.865f, 0.990f, 1.0f);    // Lighter
    static constexpr ImVec4 PrimaryActive = ImVec4(0.0f, 0.665f, 0.790f, 1.0f);   // Darker
    
    // Secondary colors
    static constexpr ImVec4 Secondary = ImVec4(1.0f, 0.271f, 0.329f, 1.0f);       // #ff4554
    static constexpr ImVec4 SecondaryHover = ImVec4(1.0f, 0.371f, 0.429f, 1.0f);  // Lighter
    static constexpr ImVec4 SecondaryActive = ImVec4(0.9f, 0.171f, 0.229f, 1.0f); // Darker
    
    // Background colors
    static constexpr ImVec4 Background = ImVec4(0.255f, 0.271f, 0.282f, 1.0f);    // #414548
    static constexpr ImVec4 BackgroundDark = ImVec4(0.155f, 0.171f, 0.182f, 1.0f);
    static constexpr ImVec4 BackgroundLight = ImVec4(0.355f, 0.371f, 0.382f, 1.0f);
    
    // Text colors
    static constexpr ImVec4 Text = ImVec4(0.95f, 0.96f, 0.98f, 1.0f);
    static constexpr ImVec4 TextDisabled = ImVec4(0.60f, 0.60f, 0.60f, 1.0f);
    
    // UI element colors
    static constexpr ImVec4 Border = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    static constexpr ImVec4 Frame = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
    static constexpr ImVec4 FrameHover = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    static constexpr ImVec4 FrameActive = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    
    // Special colors
    static constexpr ImVec4 Success = ImVec4(0.0f, 0.8f, 0.0f, 1.0f);
    static constexpr ImVec4 Warning = ImVec4(1.0f, 0.8f, 0.0f, 1.0f);
    static constexpr ImVec4 Error = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    static constexpr ImVec4 Info = ImVec4(0.0f, 0.765f, 0.890f, 1.0f);
    
    // Utility functions
    static ImVec4 WithAlpha(const ImVec4& color, float alpha) {
        return ImVec4(color.x, color.y, color.z, alpha);
    }
    
    static ImVec4 Lighten(const ImVec4& color, float amount = 0.1f) {
        return ImVec4(
            std::min(1.0f, color.x + amount),
            std::min(1.0f, color.y + amount),
            std::min(1.0f, color.z + amount),
            color.w
        );
    }
    
    static ImVec4 Darken(const ImVec4& color, float amount = 0.1f) {
        return ImVec4(
            std::max(0.0f, color.x - amount),
            std::max(0.0f, color.y - amount),
            std::max(0.0f, color.z - amount),
            color.w
        );
    }
    
    // Convert hex to ImVec4 (utility for future use)
    static ImVec4 FromHex(uint32_t hex, float alpha = 1.0f) {
        float r = ((hex >> 16) & 0xFF) / 255.0f;
        float g = ((hex >> 8) & 0xFF) / 255.0f;
        float b = (hex & 0xFF) / 255.0f;
        return ImVec4(r, g, b, alpha);
    }
};

} // namespace Pound::GUI