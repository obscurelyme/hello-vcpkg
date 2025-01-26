#ifndef ZERO_COMPONENTS_NATIVE_SCRIPT_H_
#define ZERO_COMPONENTS_NATIVE_SCRIPT_H_

#include <string>

#include "ecs/scriptableentity.h"

namespace Zero {
  class NativeScript {
    public:
      explicit NativeScript();
      ~NativeScript();

      ScriptableEntity* (*createInstance)();
      void (*destroyInstance)(NativeScript*);

      template <typename T>
      void bind() {
        createInstance = []() { return static_cast<ScriptableEntity*>(new T()); };
        destroyInstance = [](NativeScript* script) {
          delete script->instance;
          script->instance = nullptr;
        };
      }

      ScriptableEntity* instance{nullptr};
      std::string name{""};
      bool isReady{false};
      bool isFlaggedForDestroy{false};
  };
}  // namespace Zero

#endif