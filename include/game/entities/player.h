#ifndef ZERO_GAME_PLAYER_H_
#define ZERO_GAME_PLAYER_H_

#include <raylib.h>

#include "ecs/components/transform.h"
#include "ecs/ecs.h"
#include "textures/textures.h"

namespace Zero {
  class Player : public Entity {
    public:
      explicit Player();
      void init();
      void ready();
      void update(float deltaTime);
      void physicsUpdate();
      void destroy();

    private:
      Vector2 direction{.x = 0.0f, .y = 0.0f};
      float speed = 500.0f;
      SharedComponent<Texture2D> spaceship = nullptr;
      SharedComponent<Transform2D> transform = nullptr;
  };
}  // namespace Zero

#endif