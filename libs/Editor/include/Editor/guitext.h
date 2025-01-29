#ifndef ZERO_EDITOR_GUI_TEXT_H_
#define ZERO_EDITOR_GUI_TEXT_H_

#include "Editor/guielement.h"

namespace Zero {
  class GuiText : public GuiElement {
    public:
      explicit GuiText(const std::string& str = "");
      ~GuiText() = default;

      void draw() override;
      bool isValidElement() override;

      Elements type{Elements::Text};
  };
}  // namespace Zero

#endif