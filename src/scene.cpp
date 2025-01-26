#include "scene/scene.h"

#include <raylib.h>

#include <entt/entity/fwd.hpp>

#include "Logging/core.hpp"
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

  Scene::Scene() {
    // entt::entity entity = entityRegistry.create();
    // entityRegistry.emplace<Transform2DComponent>(entity);
    // entityRegistry.emplace<Sprite2DComponent>(entity);
    // entityRegistry.emplace<AudioComponent>(entity);

    // Transform2DComponent* transform = entityRegistry.try_get<Transform2DComponent>(entity);

    // auto transformView = entityRegistry.view<Transform2DComponent>();
    // for (auto entity : transformView) {
    //   auto& t = transformView.get<Transform2DComponent>(entity);
    //   if (t.active) {
    //     // NOTE: update t
    //   }
    // }

    // auto physicsView = entityRegistry.view<Collider2DComponent>();
    // for (auto entity : physicsView) {
    //   auto& p = physicsView.get<Collider2DComponent>(entity);
    //   if (p.active) {
    //     // NOTE: check for collisions with p
    //   }
    // }
  }

  void Scene::processInits() {
    // TODO: loop over every entity and call init
  }

  void Scene::processReadies() {
    // TODO: loop over every entity and call ready
  }

  void Scene::processUpdates(float) {
    // TODO: loop over every entity and call update
  }

  void Scene::processPhysicsUpdates(float) {
    // TODO: loop over every entity and call physicsUpdate
  }

  void Scene::processDestroys() {
    // TODO: loop over every entity and call destroy
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