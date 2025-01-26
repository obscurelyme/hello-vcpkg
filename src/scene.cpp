#include "scene/scene.h"

#include <raylib.h>

#include "Logging/core.hpp"
#include "ecs/components/nativescript.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/entity.h"
#include "utils/memory.h"


namespace Zero {
  Ref<Scene> activeScene;

  Ref<Scene> GetActiveScene() { return activeScene; }

  Ref<Scene> CreateNewScene() { return MakeRef<Scene>(); }

  void SetActiveScene(const Ref<Scene>& scene) { activeScene = scene; }

  void ProcessInits() { activeScene->processInits(); }

  void ProcessReadies() { activeScene->processReadies(); }

  void ProcessUpdates(float deltaTime) { activeScene->processUpdates(deltaTime); }

  float ProcessPhysicsUpdates(float fixedDeltaTime, float fixedTargetDeltaTime) {
    if (fixedDeltaTime >= fixedTargetDeltaTime) {
      activeScene->processPhysicsUpdates(fixedDeltaTime);
      return 0.0f;
    }
    return fixedDeltaTime;
  }

  void ProcessDestroys() { activeScene->processDestroys(); }

  void Render() { activeScene->render(); }

  Scene::Scene() {}

  void Scene::processInits() {
    auto view = registry.view<NativeScript>();
    for (auto entity : view) {
      auto& script = view.get<NativeScript>(entity);
      if (script.instance == nullptr) {
        script.instance = script.createInstance();
        script.instance->entity = Entity{entity, this};
        script.instance->init();
      }
    }
  }

  void Scene::processReadies() {
    auto view = registry.view<NativeScript>();
    for (auto entity : view) {
      auto& script = view.get<NativeScript>(entity);
      if (!script.isReady) {
        script.instance->ready();
        script.isReady = true;
      }
    }
  }

  void Scene::processUpdates(float deltaTime) {
    auto view = registry.view<NativeScript>();
    for (auto entity : view) {
      auto& script = view.get<NativeScript>(entity);
      if (script.isReady) {
        script.instance->update(deltaTime);
      }
    }
  }

  void Scene::processPhysicsUpdates(float fixedDeltaTime) {
    auto view = registry.view<NativeScript>();
    for (auto entity : view) {
      auto& script = view.get<NativeScript>(entity);
      if (!script.isReady) {
        script.instance->physicsUpdate(fixedDeltaTime);
      }
    }
  }

  void Scene::processDestroys() {
    auto view = registry.view<NativeScript>();
    for (auto entity : view) {
      auto& script = view.get<NativeScript>(entity);
      if (script.isFlaggedForDestroy) {
        script.destroyInstance(&script);
        view->remove(entity);
      }
    }
  }

  void Scene::render() {
    auto view = registry.view<Sprite, Transform2D>();
    for (auto entity : view) {
      // TODO: pass Sprite and Transform2D to a Renderer instance that will take care of rendering.
      view.get<Sprite>(entity).render(view.get<Transform2D>(entity));
    }
  }

  Entity Scene::createEntity() { return {registry.create(), this}; }

  Scene::~Scene() {
    registry.clear();
    ConsoleTrace("deleting scene");
  }

}  // namespace Zero