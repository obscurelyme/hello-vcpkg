#include "Editor/guiappbar.h"

namespace Zero {
  GuiAppBar::GuiAppBar(const std::string& title) : title(title) {}

  void GuiAppBar::draw() {
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New")) {
      }
      if (ImGui::MenuItem("Open")) {
      }
      if (ImGui::MenuItem("Save")) {
      }
      if (ImGui::MenuItem("Save As")) {
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}  // namespace Zero