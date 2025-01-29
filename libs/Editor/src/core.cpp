#include "Editor/core.h"

#include <fmt/printf.h>
#include <imgui.h>
#include <imgui_impl_raylib.h>
#include <raylib.h>
#include <rlImGui.h>

#include <filesystem>
#include <memory>

#include "Editor/guifont.h"
#include "Editor/guiroot.h"

namespace Zero {
  Editor::Editor() {
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplRaylib_Init();

    // Load Fonts
    io.Fonts->AddFontDefault();
    AddFont("body", "SourceCodePro-Regular.ttf", 18.0f);
    AddFont("header", "SourceCodePro-Regular.ttf", 24.0f);
    // required to be called to cache the font texture with raylib
    ImGui_ImplRaylib_BuildFontAtlas();

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
      if (tmp->isValidTree()) {
        root = tmp;
      } else {
        fmt::println("EDITOR: Invalid GUI tree detected");
      }
    };

    std::filesystem::path dir = GetApplicationDirectory();
    std::filesystem::path file = dir / "resources" / "gui" / "editor.xml";

    fileWatcher.startWatching(file, onFileChanged);
    auto tmp = std::make_shared<GuiRoot>();
    xmlParse.unmarshal(tmp.get());
    if (tmp->isValidTree()) {
      root = tmp;
    } else {
      fmt::println("EDITOR: Invalid GUI tree detected");
    }
  }

  Editor::~Editor() {}

  void Editor::cleanUp() {
    // for (auto [fontName, font] : Fonts) {
    //   delete font;
    // }
    // ImGui::GetIO().Fonts->Clear();
    ImGui_ImplRaylib_Shutdown();
    ImGui::DestroyContext();
  }

  void Editor::beginRender() {
    ImGui_ImplRaylib_ProcessEvents();
    ImGui_ImplRaylib_NewFrame();
    ImGui::NewFrame();
  }

  void Editor::endRender() {
    ImGui::Render();
    ImGui_ImplRaylib_RenderDrawData(ImGui::GetDrawData());
  }

  void Editor::render() { root->draw(); }
}  // namespace Zero