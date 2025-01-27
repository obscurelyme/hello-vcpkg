#ifndef ZERONN_EDITOR_CORE_H_
#define ZERONN_EDITOR_CORE_H_

#include "Editor/guiappbar.h"
#include "Editor/guielement.h"
#include "Editor/guipanel.h"
#include "Editor/guiroot.h"
#include "Editor/guiview.h"
#include "Editor/types.h"

namespace Zero {
  class Editor {
    public:
      Editor();
      ~Editor();

      void cleanUp();
      void initializeImGui();
      void beginRender();
      void endRender();
      void render();

      GuiRoot root;
  };
}  // namespace Zero

#endif