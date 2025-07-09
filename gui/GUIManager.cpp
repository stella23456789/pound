// Copyright 2025 Pound Emulator Project. All rights reserved.

#include "GUIManager.h"
#include "Colors.h"
#include "Base/Logging/Log.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL_opengl.h>
#include <algorithm>

namespace Pound::GUI
{

    GUIManager::GUIManager() = default;

    GUIManager::~GUIManager()
    {
        Shutdown();
    }

    bool GUIManager::Initialize(const std::string &title, int width, int height)
    {
        window = std::make_unique<Window>();

        if (!window->Initialize(title, width, height))
        {
            LOG_ERROR(Render, "Failed to initialize window");
            return false;
        }

        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        // Setup style
        ApplyTheme();

        // Setup platform/renderer backends
        ImGui_ImplSDL3_InitForOpenGL(window->GetSDLWindow(), window->GetGLContext());
        ImGui_ImplOpenGL3_Init("#version 330");

        running = true;
        return true;
    }

    void GUIManager::Shutdown()
    {
        if (!running)
            return;

        panels.clear();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        window.reset();
        running = false;
    }

    void GUIManager::RunFrame()
    {
        if (!running)
            return;

        window->ProcessEvents();

        BeginFrame();
        RenderTabBars();

        for (auto &panel : panels)
        {
            if (panel->IsVisible())
            {
                panel->Render();
            }
        }

        if (show_demo_window)
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        EndFrame();
    }

    void GUIManager::BeginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    void GUIManager::EndFrame()
    {
        ImGui::Render();

        ImGuiIO &io = ImGui::GetIO();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.08f, 0.08f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window->SwapBuffers();
    }

    void GUIManager::ApplyTheme()
    {
        ImGuiStyle &style = ImGui::GetStyle();

        // Modern theme with custom colors
        style.WindowRounding = 8.0f;
        style.FrameRounding = 4.0f;
        style.PopupRounding = 4.0f;
        style.ScrollbarRounding = 6.0f;
        style.GrabRounding = 4.0f;
        style.TabRounding = 4.0f;

        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.WindowMenuButtonPosition = ImGuiDir_Right;

        // Apply custom color scheme
        style.Colors[ImGuiCol_Text] = Colors::Text;
        style.Colors[ImGuiCol_TextDisabled] = Colors::TextDisabled;
        style.Colors[ImGuiCol_WindowBg] = Colors::WithAlpha(Colors::Background, 0.95f);
        style.Colors[ImGuiCol_ChildBg] = Colors::BackgroundDark;
        style.Colors[ImGuiCol_PopupBg] = Colors::WithAlpha(Colors::Background, 0.94f);
        style.Colors[ImGuiCol_Border] = Colors::Border;
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = Colors::BackgroundLight;
        style.Colors[ImGuiCol_FrameBgHovered] = Colors::Lighten(Colors::BackgroundLight, 0.1f);
        style.Colors[ImGuiCol_FrameBgActive] = Colors::Lighten(Colors::BackgroundLight, 0.2f);
        style.Colors[ImGuiCol_TitleBg] = Colors::BackgroundDark;
        style.Colors[ImGuiCol_TitleBgActive] = Colors::Background;
        style.Colors[ImGuiCol_TitleBgCollapsed] = Colors::WithAlpha(Colors::BackgroundDark, 0.51f);
        style.Colors[ImGuiCol_MenuBarBg] = Colors::BackgroundDark;
        style.Colors[ImGuiCol_ScrollbarBg] = Colors::WithAlpha(Colors::BackgroundDark, 0.53f);
        style.Colors[ImGuiCol_ScrollbarGrab] = Colors::BackgroundLight;
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = Colors::Lighten(Colors::BackgroundLight, 0.1f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = Colors::Lighten(Colors::BackgroundLight, 0.2f);
        style.Colors[ImGuiCol_CheckMark] = Colors::Primary;
        style.Colors[ImGuiCol_SliderGrab] = Colors::Primary;
        style.Colors[ImGuiCol_SliderGrabActive] = Colors::PrimaryActive;
        style.Colors[ImGuiCol_Button] = Colors::WithAlpha(Colors::Primary, 0.40f);
        style.Colors[ImGuiCol_ButtonHovered] = Colors::PrimaryHover;
        style.Colors[ImGuiCol_ButtonActive] = Colors::PrimaryActive;
        style.Colors[ImGuiCol_Header] = Colors::WithAlpha(Colors::Primary, 0.31f);
        style.Colors[ImGuiCol_HeaderHovered] = Colors::WithAlpha(Colors::Primary, 0.80f);
        style.Colors[ImGuiCol_HeaderActive] = Colors::Primary;
        style.Colors[ImGuiCol_Separator] = Colors::Border;
        style.Colors[ImGuiCol_SeparatorHovered] = Colors::WithAlpha(Colors::Primary, 0.78f);
        style.Colors[ImGuiCol_SeparatorActive] = Colors::Primary;
        style.Colors[ImGuiCol_ResizeGrip] = Colors::WithAlpha(Colors::Primary, 0.25f);
        style.Colors[ImGuiCol_ResizeGripHovered] = Colors::WithAlpha(Colors::Primary, 0.67f);
        style.Colors[ImGuiCol_ResizeGripActive] = Colors::WithAlpha(Colors::Primary, 0.95f);
        style.Colors[ImGuiCol_Tab] = Colors::BackgroundLight;
        style.Colors[ImGuiCol_TabHovered] = Colors::WithAlpha(Colors::Primary, 0.80f);
        style.Colors[ImGuiCol_TabActive] = Colors::Primary;
        style.Colors[ImGuiCol_TabUnfocused] = Colors::Background;
        style.Colors[ImGuiCol_TabUnfocusedActive] = Colors::Lighten(Colors::Background, 0.1f);
        style.Colors[ImGuiCol_PlotLines] = Colors::Primary;
        style.Colors[ImGuiCol_PlotLinesHovered] = Colors::PrimaryHover;
        style.Colors[ImGuiCol_PlotHistogram] = Colors::Secondary;
        style.Colors[ImGuiCol_PlotHistogramHovered] = Colors::SecondaryHover;
        style.Colors[ImGuiCol_TextSelectedBg] = Colors::WithAlpha(Colors::Primary, 0.35f);
        style.Colors[ImGuiCol_DragDropTarget] = Colors::WithAlpha(Colors::Secondary, 0.90f);
        style.Colors[ImGuiCol_NavHighlight] = Colors::Primary;
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

    void GUIManager::AddPanel(std::shared_ptr<Panel> panel)
    {
        panels.push_back(panel);
    }

    void GUIManager::RemovePanel(const std::string &name)
    {
        panels.erase(
            std::remove_if(panels.begin(), panels.end(),
                           [&name](const std::shared_ptr<Panel> &panel)
                           {
                               return panel->GetName() == name;
                           }),
            panels.end());
    }

    TabBar *GUIManager::AddTabs(const std::string &name)
    {
        auto new_bar = std::make_unique<TabBar>();
        new_bar->id = name;
        m_tab_bars.push_back(std::move(new_bar));
        return m_tab_bars.back().get();
    }

    void GUIManager::AddSubTab(TabBar *parent_bar, const std::string &name, std::function<void()> callback)
    {
        if (!parent_bar)
        {
            LOG_WARNING(Render, "Trying to add a sub-tab to a null TabBar.");
            return;
        }

        TabItem new_item;
        new_item.name = name;
        new_item.render_callback = std::move(callback);
        parent_bar->items.push_back(std::move(new_item));
    }

    void GUIManager::AddSubTab(TabBar *parent_bar, const std::string &name, const std::string &shortcut, std::function<void()> callback)
    {
        if (!parent_bar)
        {
            LOG_WARNING(Render, "Trying to add a sub-tab to a null TabBar.");
            return;
        }

        TabItem new_item;
        new_item.name = name;
        new_item.shortcut = shortcut;
        new_item.render_callback = std::move(callback);
        parent_bar->items.push_back(std::move(new_item));
    }

    void GUIManager::AddSubTab(TabBar *parent_bar, const std::string &name, bool *p_selected, std::function<void(bool)> callback)
    {
        if (!parent_bar)
        {
            LOG_WARNING(Render, "Trying to add a sub-tab to a null TabBar.");
            return;
        }

        TabItem new_item;
        new_item.name = name;
        new_item.p_selected = p_selected;
        new_item.checked_callback  = std::move(callback);
        parent_bar->items.push_back(std::move(new_item));
    }

    void GUIManager::AddSubTab(TabBar *parent_bar, const std::string &name, bool *p_selected, const std::string &shortcut, std::function<void(bool)> callback)
    {
        if (!parent_bar)
        {
            LOG_WARNING(Render, "Trying to add a sub-tab to a null TabBar.");
            return;
        }

        TabItem new_item;
        new_item.name = name;
        new_item.shortcut = shortcut;
        new_item.p_selected = p_selected;
        new_item.checked_callback  = std::move(callback);
        parent_bar->items.push_back(std::move(new_item));
    }

    void GUIManager::RenderTabBarContents(TabBar &bar)
    {
        for (const auto &item : bar.items)
        {
            if (item.nested_tabs)
            {
                if (ImGui::BeginMenu(item.name.c_str()))
                {
                    RenderTabBarContents(*item.nested_tabs);
                    ImGui::EndMenu();
                }
            }
            else
            {
                const char *shortcut = item.shortcut.empty() ? nullptr : item.shortcut.c_str();
                if (ImGui::MenuItem(item.name.c_str(), shortcut, item.p_selected))
                {
                    if (item.p_selected && item.checked_callback)
                    {
                        item.checked_callback(*item.p_selected);
                    }
                }
            }
        }
    }

    void GUIManager::RenderTabBars()
    {
        if (ImGui::BeginMainMenuBar())
        {
            for (const auto &bar_ptr : m_tab_bars)
            {
                if (ImGui::BeginMenu(bar_ptr->id.c_str()))
                {
                    RenderTabBarContents(*bar_ptr);
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();
        }
    }
}