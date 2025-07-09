// Copyright 2025 Pound Emulator Project. All rights reserved.
#pragma once

#include <string>
#include <imgui.h>

namespace Pound::GUI
{

    class Panel
    {
    public:
        Panel(const std::string &name) : name(name) {}
        virtual ~Panel() = default;

        virtual void Render() = 0;

        const std::string &GetName() const { return name; }
        bool* IsVisible() { return &visible; }
        void SetVisible(bool vis) { visible = vis; }

    protected:
        std::string name;
        bool visible = true;
    };

} // namespace Pound::GUI