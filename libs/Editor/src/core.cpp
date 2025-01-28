#include "Editor/core.h"

#include <fmt/printf.h>
#include <raylib.h>
#include <rlImGui.h>

#include <filesystem>
#include <memory>

#include "Editor/guiroot.h"

namespace Zero {
  Editor::Editor() {
    rlImGuiSetup(true);
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = convertColor(DarkPaleBlue);
    style.Colors[ImGuiCol_TitleBg] = convertColor(OfficeBlue);
    style.Colors[ImGuiCol_TitleBgActive] = convertColor(OfficeBlue);
    style.Colors[ImGuiCol_TitleBgCollapsed] = convertColor(OfficeBlue);
    style.Colors[ImGuiCol_Text] = convertColor(OffWhite);
    root = std::make_shared<GuiRoot>();

    onFileChanged = [this]() -> void {
      xmlParse.readFile();
      auto tmp = std::make_shared<GuiRoot>();
      xmlParse.unmarshal(tmp.get());
      root = tmp;
    };

    std::filesystem::path dir = GetApplicationDirectory();
    std::filesystem::path file = dir / "resources" / "gui" / "editor.xml";

    fileWatcher.startWatching(file, onFileChanged);
    xmlParse.unmarshal(root.get());
  }

  Editor::~Editor() { cleanUp(); }

  void Editor::cleanUp() { rlImGuiShutdown(); }

  void Editor::beginRender() { rlImGuiBegin(); }

  void Editor::endRender() { rlImGuiEnd(); }

  void Editor::render() { root->draw(); }
}  // namespace Zero