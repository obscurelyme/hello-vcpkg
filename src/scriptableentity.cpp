#include "ecs/scriptableentity.h"

namespace Zero {
  ScriptableEntity::ScriptableEntity() : entity({}) {
    ConsoleTrace(fmt::format(fmt::runtime("SCRIPTABLE ENTITY: {}"), "Created"));
  }

  ScriptableEntity::~ScriptableEntity() {
    ConsoleTrace(fmt::format(fmt::runtime("SCRIPTABLE ENTITY: {}"), "Destroyed"));
  };

  std::string ScriptableEntity::scriptName() { return "ScriptableEntity"; }
}  // namespace Zero
