#include "stats.h"


void UI::Stats(bool& show_stats, float deltaTime, float main_window_width, float main_window_height , float last_mouse_pos_x, float last_mouse_pos_y) {
  if (show_stats) {
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
    // See: https://github.com/ocornut/imgui/issues/1657
    // ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f,0.5f));
    ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowBgAlpha(0.3f);

    ImGui::Begin("Stats", p_open, window_flags);
    ImGui::Text("[Frame rate] %.1f frame/s", 1 / (deltaTime*0.001));
    ImGui::Text("[Delta time] %.3f ms/frame", deltaTime);
    ImGui::Text("[UI frame rate] %.1f frame/s", ImGui::GetIO().Framerate);
    ImGui::Text("[UI delta time] %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("[Main window dimension] %.0f x %.0f", main_window_width, main_window_height);
    ImGui::Text("[Cursor position] %.0f x %.0f", last_mouse_pos_x, last_mouse_pos_y);
    ImGui::End();
  }
}