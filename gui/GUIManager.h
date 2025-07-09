// Copyright 2025 Pound Emulator Project. All rights reserved.
#pragma once

#include <memory>
#include <vector>
#include <functional>
#include "Window.h"
#include "Panel.h"

namespace Pound::GUI
{

    struct TabBar;

    struct TabItem
    {
        std::string name;
        std::string shortcut;
        bool *p_selected = nullptr;
        std::function<void()> render_callback;
        std::function<void(bool)> checked_callback; 
        std::unique_ptr<TabBar> nested_tabs = nullptr;
    };

    struct TabBar
    {
        std::string id;
        std::vector<TabItem> items;
        bool is_visible = true;
    };

    class GUIManager
    {
    public:
        GUIManager();
        ~GUIManager();

        bool Initialize(const std::string &title, int width, int height);
        void Shutdown();

        void RunFrame();
        bool IsRunning() const { return running && window && !window->ShouldClose(); }

        Window *GetWindow() const { return window.get(); }

        void AddPanel(std::shared_ptr<Panel> panel);
        void RemovePanel(const std::string &name);

        TabBar *AddTabs(const std::string &name);
        void AddSubTab(TabBar *parent_bar, const std::string &name, std::function<void()> callback = nullptr);
        void AddSubTab(TabBar *parent_bar, const std::string &name, const std::string &shortcut, std::function<void()> callback);
        void AddSubTab(TabBar *parent_bar, const std::string &name, bool *p_selected, std::function<void(bool)> callback = nullptr);
        void AddSubTab(TabBar *parent_bar, const std::string &name, bool *p_selected, const std::string &shortcut, std::function<void(bool)> callback = nullptr);

    private:
        void BeginFrame();
        void EndFrame();
        void ApplyTheme();
        void RenderTabBars();
        void RenderTabBarContents(TabBar &bar);

        std::unique_ptr<Window> window;
        std::vector<std::shared_ptr<Panel>> panels;
        bool running = false;
        bool show_demo_window = false;
        std::vector<std::unique_ptr<TabBar>> m_tab_bars;
    };

} // namespace Pound::GUI