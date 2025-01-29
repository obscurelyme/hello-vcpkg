#ifndef ZERO_EDITOR_GUI_VIEW_H_
#define ZERO_EDITOR_GUI_VIEW_H_

#include <optional>

#include "Editor/guielement.h"

namespace Zero {
  class GuiViewInput {
    public:
      // Interpret the height value as a percent.
      std::optional<bool> useHeightPercent{std::nullopt};
      // Interpret the width value as a percent.
      std::optional<bool> useWidthPercent{std::nullopt};
      float height;
      float width;
  };

  class GuiView : public GuiElement {
    public:
      GuiView();
      GuiView(const GuiViewInput&);
      ~GuiView() = default;

      void draw() override;
      Elements type{Elements::View};
  };
}  // namespace Zero

#endif  // ZERO_EDITOR_GUI_VIEW_H