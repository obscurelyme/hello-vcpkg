#ifndef ZERO_ECS_SCRIPTABLEENTITY_H_
#define ZERO_ECS_SCRIPTABLEENTITY_H_

#include <fmt/base.h>
#include <fmt/format.h>

#include "Logging/core.hpp"
#include "entity.h"

namespace Zero {
  class ScriptableEntity {
    public:
      ScriptableEntity() : entity({entt::null, nullptr}) {
        ConsoleTrace(fmt::format(fmt::runtime("SCRIPTABLE ENTITY: {}"), "Created"));
      }
      virtual ~ScriptableEntity() { ConsoleTrace(fmt::format(fmt::runtime("SCRIPTABLE ENTITY: {}"), "Destroyed")); };

      virtual std::string scriptName() { return "ScriptableEntity"; }

      // NOTE: this is how it will actually be
    protected:
      virtual void init() {}
      virtual void ready() {}
      virtual void update(float) {}
      virtual void physicsUpdate(float) {}
      virtual void destroy() {}

      template <typename T>
      T* getComponent() {
        return &entity.getComponent<T>();
      }

      Entity entity;

      friend class Scene;
  };
}  // namespace Zero

#endif