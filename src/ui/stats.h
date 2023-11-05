#include <imgui.h>
#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"


namespace UI {
  void Stats(bool& show_stats, float deltaTime, float main_window_width, float main_window_height, float last_mouse_pos_x, float last_mouse_pos_y);
}