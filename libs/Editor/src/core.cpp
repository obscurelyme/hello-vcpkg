#include "Editor/core.h"

#include <rlImGui.h>

namespace Zero {
  Editor::Editor() {
    rlImGuiSetup(true);
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = convertColor(DarkPaleBlue);
    style.Colors[ImGuiCol_TitleBg] = convertColor(OfficeBlue);
    style.Colors[ImGuiCol_TitleBgActive] = convertColor(OfficeBlue);
    style.Colors[ImGuiCol_TitleBgCollapsed] = convertColor(OfficeBlue);
    style.Colors[ImGuiCol_Text] = convertColor(OffWhite);
  }

  Editor::~Editor() { cleanUp(); }

  void Editor::cleanUp() { rlImGuiShutdown(); }

  void Editor::beginRender() { rlImGuiBegin(); }

  void Editor::endRender() { rlImGuiEnd(); }

  void Editor::render() { root.draw(); }
}  // namespace Zero