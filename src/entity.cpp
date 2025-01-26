#include "ecs/entity.h"

namespace Zero {
  Entity::Entity(EntityId id, Scene* scene) : id(id), scene(scene) {}

  Entity::~Entity() {
    // NOTE: remove this entity from all helper maps so that the lifetime methods aren't mistakenly invoked.
  }

  void Entity::init() {}
  void Entity::ready() {}
  void Entity::update(float) {}
  void Entity::physicsUpdate(float) {}
  void Entity::destroy() {}
}  // namespace Zero
