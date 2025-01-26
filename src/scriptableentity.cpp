#include "ecs/scriptableentity.h"

#include "uuid/uuid.h"


namespace Zero {
  ScriptableEntity::ScriptableEntity() : entity({}), uuid(randomUUID()) {
    ConsoleTrace(fmt::format(fmt::runtime("SCRIPTABLE ENTITY: {}"), "Created"));
  }

  ScriptableEntity::~ScriptableEntity() {
    ConsoleTrace(fmt::format(fmt::runtime("SCRIPTABLE ENTITY: {}"), "Destroyed"));
  };

  std::string ScriptableEntity::scriptName() { return "ScriptableEntity"; }
}  // namespace Zero
