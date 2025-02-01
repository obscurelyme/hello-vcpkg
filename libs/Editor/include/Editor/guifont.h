#ifndef ZERO_EDITOR_GUI_FONT_H_
#define ZERO_EDITOR_GUI_FONT_H_

#include <imgui.h>
#include <raylib.h>

#include <filesystem>
#include <string>
#include <unordered_map>

namespace Zero {
  const std::filesystem::path fontPath = GetApplicationDirectory();
  const std::filesystem::path fontFilePath = fontPath / "resources" / "fonts";
  inline std::unordered_map<std::string, ImFont*> Fonts{};

  inline ImFont* BodyFont() { return Fonts["body"]; }
  inline ImFont* HeaderFont() { return Fonts["header"]; }

  inline void AddFont(const std::string& name, const std::string& fontFile, float size = 16.0f) {
    // Add to map
    auto io = ImGui::GetIO();
    auto font = io.Fonts->AddFontFromFileTTF((fontFilePath / fontFile).string().c_str(), size, nullptr,
                                             io.Fonts->GetGlyphRangesDefault());

    IM_ASSERT(font != nullptr);

    Fonts.emplace(name, font);
  }
}  // namespace Zero

#endif