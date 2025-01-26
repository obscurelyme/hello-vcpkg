#ifndef ZERO_ECS_SCRIPTABLEENTITY_H_
#define ZERO_ECS_SCRIPTABLEENTITY_H_

#include <fmt/base.h>
#include <fmt/format.h>

#include <string>

#include "ecs/entity.h"

namespace Zero {
  class ScriptableEntity {
    public:
      ScriptableEntity();
      virtual ~ScriptableEntity();

      virtual std::string scriptName();

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