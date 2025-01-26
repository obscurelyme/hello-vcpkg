#include "ecs/entity.h"

#include <entt/entity/entity.hpp>

#include "uuid/uuid.h"

namespace Zero {
  Entity::Entity() : uuid(randomUUID()), id(entt::null), scene(nullptr) {
    printTrace("Entity created via default constructor");
  };

  Entity::Entity(EntityId id, Scene* scene) : uuid(randomUUID()), id(id), scene(scene) {
    printTrace("Entity created via explicit constructor");
  }

  Entity::Entity(const Entity& other) : uuid(other.uuid), id(other.id), scene(other.scene) {
    printTrace("Entity created via copy constructor");
  }

  Entity& Entity::operator=(const Entity& other) {
    if (this != &other) {
      uuid = other.uuid;
      id = other.id;
      scene = other.scene;

      printTrace("Entity copied");
    }

    return *this;
  }
}  // namespace Zero
