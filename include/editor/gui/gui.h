#ifndef ZERO_EDITOR_GUI_H_
#define ZERO_EDITOR_GUI_H_

#include <raylib.h>

#include "scene/scene.h"

namespace Zero {
  class GuiElement {
    public:
      virtual ~GuiElement() = default;
      void draw();

      // Callback function to invoke when the element is drawn
      void (*onDraw)() = nullptr;
  };

  class Editor {
    public:
      Editor();
      ~Editor();

      void draw();
      void setScene(Scene* scene);
      void toggle();

    private:
      Scene* scene;
      bool enabled{true};
  };  // namespace Editor
}  // namespace Zero

#endif
