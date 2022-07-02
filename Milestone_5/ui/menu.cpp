#include "menu.h"


void UI::Menu(bool& show_menu, bool& show_stats, Camera& camera, ImVec4& clear_color) {
  if (show_menu) {
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    bool* p_open = NULL;

    ImGui::Begin("Menu", p_open, window_flags);
    ImGui::Checkbox("[Display stats]", &show_stats);
    ImGui::SliderFloat("[FOV]", &camera.FOV(), 30.0f, 120.0f);
    ImGui::SliderFloat("[Camera speed]", &camera.Speed(), 0.003f, 0.01f);
    ImGui::ColorEdit3("[Background color]", (float*)&clear_color);
    ImGui::End();
   }
}