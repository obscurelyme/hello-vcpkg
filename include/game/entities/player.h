#ifndef ZERO_GAME_PLAYER_H_
#define ZERO_GAME_PLAYER_H_

#include <raylib.h>

#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/entity.h"

namespace Zero {
  class Player : public Entity {
    public:
      explicit Player();
      void init();
      void ready();
      void update(float);
      void physicsUpdate(float);
      void destroy();

    private:
      Vector2 direction{.x = 0.0f, .y = 0.0f};
      float speed = 500.0f;
      Shared<Sprite> spaceship = nullptr;
      Shared<Transform2D> transform = nullptr;
  };
}  // namespace Zero

#endif