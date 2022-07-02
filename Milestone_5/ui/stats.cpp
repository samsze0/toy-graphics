#include "stats.h"


void UI::Stats(bool& show_stats, float deltaTime) {
  if (show_stats) {
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    bool* p_open = NULL;

    ImGui::Begin("Stats", p_open, window_flags);
    ImGui::Text("[Frame rate] %.1f", 1 / (deltaTime*0.001));
    ImGui::Text("[Delta time] %.3f ms/frame", deltaTime);
    ImGui::Text("[UI frame rate] %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("[UI delta time] %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::End();
  }
}