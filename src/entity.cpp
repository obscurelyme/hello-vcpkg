#include "ecs/entity.h"

#include <entt/entity/entity.hpp>

namespace Zero {
  Entity::Entity() : id(entt::null), scene(nullptr) { printTrace("Entity created via default constructor"); };

  Entity::Entity(EntityId id, Scene* scene) : id(id), scene(scene) {
    printTrace("Entity created via explicit constructor");
  }

  Entity::Entity(const Entity& other) : id(other.id), scene(other.scene) {
    printTrace("Entity created via copy constructor");
  }

  Entity& Entity::operator=(const Entity& other) {
    id = other.id;
    scene = other.scene;
    printTrace("Entity created via copy assignment");
    return *this;
  }
}  // namespace Zero
