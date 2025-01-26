#ifndef ZERO_ECS_ENTITY_H_
#define ZERO_ECS_ENTITY_H_

#include <entt/entt.hpp>
#include <string>

#include "ecs/components/component.h"

namespace Zero {
  class Entity {
    public:
      explicit Entity();
      virtual ~Entity();
      virtual void init();
      virtual void ready();
      virtual void update(float);
      virtual void physicsUpdate(float);
      virtual void destroy();

      void addComponent(const SharedComponent& component);
      void removeComponent(const SharedComponent& component);
      SharedComponent getComponent(const ComponentType& type);
      // template <typename T>
      // bool hasComponent() {}

      // uuid string
      std::string entityId;
  };  // namespace Zero
}  // namespace Zero

#endif