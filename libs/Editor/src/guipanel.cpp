#include "Editor/guipanel.h"

namespace Zero {
  GuiPanel::GuiPanel(const std::string& title) : title{title} {
    YGNodeSetContext(node, this);
    YGNodeStyleSetWidth(node, size.x);
    YGNodeStyleSetHeight(node, size.y);
    YGNodeStyleSetPositionType(node, YGPositionTypeRelative);
    YGNodeStyleSetDisplay(node, YGDisplayFlex);
  }

  void GuiPanel::draw() {
    float top = getTop();
    float left = getLeft();
    float width = getWidth();
    float height = getHeight();

    ImGui::SetNextWindowPos(ImVec2{left, top});
    ImGui::SetNextWindowSize(ImVec2{width, height});

    ImGui::Begin(title.c_str(), &open, flags);
    ImGui::TextWrapped("%s", title.c_str());
    ImGui::Separator();
    drawChildren();
    ImGui::End();
  }
}  // namespace Zero