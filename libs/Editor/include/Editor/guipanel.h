#ifndef ZERO_EDITOR_GUI_PANEL_H_
#define ZERO_EDITOR_GUI_PANEL_H_

#include <string>

#include "Editor/guielement.h"

namespace Zero {
  class GuiPanel : public GuiElement {
    public:
      explicit GuiPanel(const std::string&);
      ~GuiPanel() = default;

      void draw() override;

      std::string title{""};
      bool open{true};
      ImVec2 position{0, 0};
      ImVec2 size{250, 250};
      ImGuiWindowFlags flags{ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                             ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar};
  };
}  // namespace Zero

#endif  // ZERO_EDITOR_GUI_PANEL_H_