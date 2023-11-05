#include "menu.h"


void UI::Menu(bool& show_menu, bool& show_stats, Camera& camera, ImVec4& clear_color) {
  if (show_menu) {
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    window_flags |= ImGuiWindowFlags_NoSavedSettings;
    bool* p_open = NULL;

    // Always position window at center of the main window, pivot at center
    // ImGui::SetNextWindowPos(ImVec2(main_window_width/2, main_window_height/2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    // Alternative solution: ImGUI will access the same underlying glfw calls to gain information about the viewport
    auto io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f,0.5f));
    ImGui::SetNextWindowBgAlpha(0.8f);

    ImGui::Begin("Menu", p_open, window_flags);
    ImGui::Checkbox("[Display stats]", &show_stats);
    ImGui::SliderFloat("[FOV]", &camera.FOV(), 30.0f, 120.0f);
    ImGui::SliderFloat("[Camera speed]", &camera.Speed(), 0.003f, 0.01f);
    ImGui::ColorEdit3("[Background color]", (float*)&clear_color);
    ImGui::End();
   }
}