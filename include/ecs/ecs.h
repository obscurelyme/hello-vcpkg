#ifndef ZERO_ECS_H_
#define ZERO_ECS_H_

#include <fmt/format.h>

#include <bitset>
#include <memory>
#include <unordered_map>

#include "Logging/core.hpp"
#include "ecs/components/component.h"
#include "ecs/components/renderable.h"
#include "ecs/components/transform.h"
#include "uuid/uuid.h"

namespace Zero {
  using EntityId = std::string;
  using ComponentBitset = std::bitset<32>;

  class Entity;
  inline std::unordered_map<EntityId, Entity*> entities;
  inline std::unordered_map<EntityId, Entity*> entitiesToInit;
  inline std::unordered_map<EntityId, Entity*> entitiesToMakeReady;
  inline std::unordered_map<EntityId, Entity*> entitiesToDestroy;
  inline std::unordered_map<EntityId, Entity*> entitiesCommittedToInit;
  inline std::unordered_map<EntityId, Entity*> entitiesCommittedToReady;

  class EntityManager {
    public:
      static EntityManager* Create() {
        if (instance == nullptr) {
          instance = new EntityManager();
          ConsoleLog("EntityManager successfully created");
        } else {
          ConsoleWarn("Attempt to recreate existing EntityManager failed");
        }

        return instance;
      }

      ~EntityManager() {
        entityComponentMask.clear();
        renderables.clear();
        transforms.clear();
        ConsoleLog("EntityManager successfully destroyed");
      }

      static void AddComponent(EntityId entityId, std::shared_ptr<Component> component) {
        switch (component->type) {
          case Zero::ComponentType::Renderable: {
            auto convertedPtr = std::dynamic_pointer_cast<Renderable>(component);
            instance->renderables[entityId] = convertedPtr;
            instance->entityComponentMask[entityId].set(static_cast<int>(ComponentType::Renderable));
            break;
          }
          case Zero::ComponentType::Transform: {
            auto convertedPtr = std::dynamic_pointer_cast<Transform2D>(component);
            instance->transforms[entityId] = convertedPtr;
            instance->entityComponentMask[entityId].set(static_cast<int>(ComponentType::Transform));
            break;
          }
          default: {
            ConsoleErr("Unknown component type added to entity manager, ignoring");
          }
        }
      }

      static void RemoveComponent(EntityId entityId, const std::shared_ptr<Component> component) {
        switch (component->type) {
          case Zero::ComponentType::Renderable: {
            auto convertedPtr = std::dynamic_pointer_cast<Renderable>(component);
            instance->renderables.erase(entityId);
            break;
          }
          default: {
            ConsoleErr("Unknown component type added to entity manager, ignoring");
          }
        }
      }

      static SharedComponent<Component> GetComponent(const std::string& entityId, const ComponentType& type) {
        if (instance->entityComponentMask[entityId].test(static_cast<int>(type))) {
          switch (type) {
            case Zero::ComponentType::Transform: {
              return instance->transforms[entityId];
            }
            case Zero::ComponentType::Renderable: {
              return instance->renderables[entityId];
            }
            case Zero::ComponentType::Physics: {
              // TODO: return physics component
            }
            default: {
              ConsoleErr("Could not find appropriate component when calling \"GetComponent\"");
              return nullptr;
            }
          }
        }
        return nullptr;
      }

      static void Render() {
        for (auto it = instance->renderables.begin(); it != instance->renderables.end(); ++it) {
          it->second->render();
        }
      }

      static EntityManager* Get() { return instance; }

      static void Destroy() {
        Zero::entities.clear();
        Zero::entitiesToInit.clear();
        Zero::entitiesToMakeReady.clear();
        Zero::entitiesToDestroy.clear();
        Zero::entitiesCommittedToInit.clear();
        Zero::entitiesCommittedToReady.clear();

        delete instance;
      }

    private:
      static EntityManager* instance;
      EntityId nextEntityId;

      std::unordered_map<EntityId, ComponentBitset> entityComponentMask;
      std::unordered_map<EntityId, SharedComponent<Renderable>> renderables;
      std::unordered_map<EntityId, SharedComponent<Transform2D>> transforms;
  };

  class Entity {
    public:
      explicit Entity() {
        this->entityId = randomUUID();
        entities[this->entityId] = this;
        entitiesToInit[this->entityId] = this;
        entitiesToMakeReady[this->entityId] = this;
      }
      virtual ~Entity() {
        // NOTE: remove this entity from all helper maps so that the lifetime methods aren't mistakenly invoked.
        entities.erase(this->entityId);
        entitiesToInit.erase(this->entityId);
        entitiesToMakeReady.erase(this->entityId);
        entitiesToDestroy.erase(this->entityId);
        entitiesCommittedToInit.erase(this->entityId);
        entitiesCommittedToReady.erase(this->entityId);
      };
      virtual void init() = 0;
      virtual void ready() = 0;
      virtual void update(float deltaTime) = 0;
      virtual void physicsUpdate() = 0;
      virtual void destroy() = 0;

      void addComponent(const std::shared_ptr<Component>& component) {
        component->entityId = this->entityId;
        EntityManager::AddComponent(this->entityId, component);
      }

      void removeComponent(const std::shared_ptr<Component>& component) {
        component->entityId = "";
        EntityManager::RemoveComponent(this->entityId, component);
      }

      SharedComponent<Component> getComponent(const ComponentType& type) {
        return EntityManager::GetComponent(this->entityId, type);
      }

      // uuid string
      EntityId entityId;
  };  // namespace Zero

  inline void ProcessInits() {
    entitiesCommittedToInit.swap(entitiesToInit);

    for (auto it = entitiesCommittedToInit.begin(); it != entitiesCommittedToInit.end(); ++it) {
      it->second->init();
    }

    entitiesCommittedToInit.clear();
  }

  inline void ProcessReadies() {
    entitiesCommittedToReady.swap(entitiesToMakeReady);

    for (auto it = entitiesCommittedToReady.begin(); it != entitiesCommittedToReady.end(); ++it) {
      it->second->ready();
    }

    entitiesCommittedToReady.clear();
  }
}  // namespace Zero

#endif