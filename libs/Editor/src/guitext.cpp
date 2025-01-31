#include "Editor/guitext.h"

#include <fmt/base.h>
#include <fmt/format.h>
#include <imgui.h>

#include "Editor/guifont.h"

namespace Zero {
  GuiText::GuiText(const std::string& str) {
    type = Elements::Text;
    innerText = str;
    YGNodeSetContext(node, this);
  }

  void GuiText::draw() {
    calculate();

    ImGui::PushFont(BodyFont());
    ImGui::TextWrapped("%s", innerText.c_str());
    ImGui::PopFont();
  }

  bool GuiText::isValidElement() {
    if (!innerText.empty() && parent != nullptr && parent->type == Elements::Panel) {
      return true;
    }
    fmt::println(fmt::runtime("GuiText: Invalid element [Has text: {:s}, Has Parent: {:s}, Parent is View: {:s}]"),
                 !innerText.empty() ? "Y" : "N", parent != nullptr ? "Y" : "N",
                 parent->type == Elements::Panel ? "Y" : "N");
    return false;
  }
}  // namespace Zero