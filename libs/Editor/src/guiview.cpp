#include "Editor/guiview.h"

namespace Zero {
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
}  // namespace Zero