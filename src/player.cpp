#include "game/entities/player.h"

#include <raymath.h>

#include <memory>

#include "textures/textures.h"

Zero::Player::Player() : Zero::Entity() {}

void Zero::Player::init() {
  this->spaceship = std::make_shared<Zero::Texture2D>("spaceship.png");
  this->addComponent(this->spaceship);
}

void Zero::Player::ready() {}

void Zero::Player::update(float deltaTime) {
  direction.x = static_cast<int>(IsKeyDown(KeyboardKey::KEY_D)) - static_cast<int>(IsKeyDown(KeyboardKey::KEY_A));
  direction.y = static_cast<int>(IsKeyDown(KeyboardKey::KEY_S)) - static_cast<int>(IsKeyDown(KeyboardKey::KEY_W));
  direction = Vector2Normalize(direction);
  direction = Vector2Scale(direction, speed * deltaTime);
  spaceship->position = Vector2Add(spaceship->position, direction);
}

void Zero::Player::physicsUpdate() {}

void Zero::Player::destroy() {}