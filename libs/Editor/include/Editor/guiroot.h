#ifndef ZERO_EDITOR_GUI_ROOT_H_
#define ZERO_EDITOR_GUI_ROOT_H_

#include "Editor/guielement.h"

namespace Zero {
  class GuiRoot : public GuiElement {
    public:
      explicit GuiRoot();
      ~GuiRoot() = default;

      void draw() override;
  };
}  // namespace Zero

#endif