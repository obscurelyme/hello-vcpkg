#include "Editor/guipanel.h"

#include <fmt/base.h>
#include <fmt/format.h>

namespace Zero {
  GuiPanel::GuiPanel(const std::string& panelTitle) {
    title = panelTitle;
    YGNodeSetContext(node, this);
    YGNodeStyleSetWidth(node, size.x);
    YGNodeStyleSetHeight(node, size.y);
    YGNodeStyleSetPositionType(node, YGPositionTypeRelative);
    YGNodeStyleSetDisplay(node, YGDisplayFlex);
  }

  void GuiPanel::draw() {
    calculate();
    float top = getTop();
    float left = getLeft();
    float width = getWidth();
    float height = getHeight();

    // NOTE:
    // I really thought that this would be a good idea, but it turns out that the flex window calculates only
    // relative position to the parent container. So, if the parent container is not the root, then the position
    // needs to still account for where it's parent is located.
    // https://github.com/facebook/yoga/issues/1053#issuecomment-757537766
    calculatedSize = {width, height};
    calculatedPosition = {left + this->parent->calculatedPosition.x, top + this->parent->calculatedPosition.y};

    ImGui::SetNextWindowPos(ImVec2{calculatedPosition.x, calculatedPosition.y});
    ImGui::SetNextWindowSize(ImVec2{width, height});

    ImGui::Begin(title.c_str(), &open, flags);
    ImGui::TextWrapped("%s", title.c_str());
    ImGui::Separator();
    drawChildren();
    ImGui::End();
  }
}  // namespace Zero