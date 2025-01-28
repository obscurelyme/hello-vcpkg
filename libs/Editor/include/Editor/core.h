#ifndef ZERONN_EDITOR_CORE_H_
#define ZERONN_EDITOR_CORE_H_

#include "Editor/guiroot.h"
#include "Editor/xmlparse.h"

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
      XmlParse xmlParse;
  };
}  // namespace Zero

#endif