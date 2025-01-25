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

      static SharedComponent GetComponent(const std::string& entityId, const ComponentType& type) {
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
      std::unordered_map<EntityId, Shared<Renderable>> renderables;
      std::unordered_map<EntityId, Shared<Transform2D>> transforms;
  };

  void ProcessInits();
  void ProcessReadies();
}  // namespace Zero

#endif