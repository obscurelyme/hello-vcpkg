#ifndef ZERO_EDITOR_GUI_APP_BAR_H_
#define ZERO_EDITOR_GUI_APP_BAR_H_

#include <string>

#include "Editor/guielement.h"

namespace Zero {
  class GuiAppBar : GuiElement {
    public:
      explicit GuiAppBar(const std::string&);
      void draw() override;

      std::string title;
  };
}  // namespace Zero

#endif  // ZERO_EDITOR_GUI_APP_BAR_H_