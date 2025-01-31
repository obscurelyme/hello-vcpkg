#ifndef ZERONN_EDITOR_CORE_H_
#define ZERONN_EDITOR_CORE_H_

#include <memory>
#include <mutex>

#include "Editor/filewatcher.h"
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

      std::function<void()> onFileChanged;
      std::shared_ptr<GuiRoot> root{nullptr};
      std::mutex rootMutex;
      XmlParse xmlParse;
      FileWatcher fileWatcher;
  };
}  // namespace Zero

#endif