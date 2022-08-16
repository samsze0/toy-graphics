#include "demo.h"


void UI::Demo(bool& show_menu) {
  if (show_menu)
    ImGui::ShowDemoWindow(&show_menu);
}