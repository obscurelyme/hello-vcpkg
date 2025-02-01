#include "Editor/guiview.h"

#include <YGNode.h>
#include <fmt/format.h>
#include <imgui.h>

namespace Zero {
  GuiView::GuiView() {
    type = Elements::View;
    YGNodeSetAlwaysFormsContainingBlock(node, true);
    YGNodeSetContext(node, this);
  }

  GuiView::GuiView(const GuiViewInput& input) {
    if (input.useHeightPercent.has_value() && input.useHeightPercent.value()) {
      YGNodeStyleSetHeightPercent(node, input.height);
    } else {
      YGNodeStyleSetHeight(node, input.height);
    }
    if (input.useWidthPercent.has_value() && input.useWidthPercent.value()) {
      YGNodeStyleSetWidthPercent(node, input.width);
    } else {
      YGNodeStyleSetWidth(node, input.width);
    }
    YGNodeSetContext(node, this);
  }

  void GuiView::draw() {
    calculate();
    drawChildren();
  }
}  // namespace Zero