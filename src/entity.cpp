#include "ecs/entity.h"

#include "ecs/components/component.h"
#include "ecs/ecs.h"
#include "uuid/uuid.h"

Zero::Entity::Entity() {
  this->entityId = randomUUID();
  entities[this->entityId] = this;
  entitiesToInit[this->entityId] = this;
  entitiesToMakeReady[this->entityId] = this;
}

Zero::Entity::~Entity() {
  // NOTE: remove this entity from all helper maps so that the lifetime methods aren't mistakenly invoked.
  Zero::entities.erase(this->entityId);
  entitiesToInit.erase(this->entityId);
  entitiesToMakeReady.erase(this->entityId);
  entitiesToDestroy.erase(this->entityId);
  entitiesCommittedToInit.erase(this->entityId);
  entitiesCommittedToReady.erase(this->entityId);
}

void Zero::Entity::init() {}
void Zero::Entity::ready() {}
void Zero::Entity::update(float) {}
void Zero::Entity::physicsUpdate(float) {}
void Zero::Entity::destroy() {}

void Zero::Entity::addComponent(const SharedComponent& component) {
  component->entityId = this->entityId;
  EntityManager::AddComponent(this->entityId, component);
}

void Zero::Entity::removeComponent(const SharedComponent& component) {
  component->entityId = "";
  EntityManager::RemoveComponent(this->entityId, component);
}

Zero::SharedComponent Zero::Entity::getComponent(const ComponentType& type) {
  return EntityManager::GetComponent(this->entityId, type);
}