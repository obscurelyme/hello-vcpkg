#include "ecs/components/sprite.h"

#include <raylib.h>
#include <raymath.h>

#include "Logging/core.hpp"
#include "ecs/components/transform.h"

const std::string assetsDir = "assets";
const std::string spritesDir = "sprites";
const std::filesystem::path applicationDir = GetApplicationDirectory();
const std::filesystem::path Zero::Sprite::assetDir = applicationDir / assetsDir / spritesDir;

namespace Zero {
  const float DEFAULT_SCALE = 1.0f;
  const float DFAULT_ROTATION = 0.0f;
}  // namespace Zero

Zero::Sprite::Sprite(const std::string& fileName) noexcept : Zero::Renderable() {
  this->filePath = (this->assetDir / fileName).string();
  this->texture = LoadTexture(this->filePath.c_str());
  this->position = Vector2{.x = 0.0f, .y = 0.0f};
  this->rotation = Zero::DFAULT_ROTATION;
  this->scale = Zero::DEFAULT_SCALE;
  this->tint = WHITE;
}

Zero::Sprite::~Sprite() noexcept {
  if (IsTextureValid(this->texture)) {
    UnloadTexture(this->texture);
    return;
  }
  ConsoleErr("Unable to unload texture because it was not loaded into the GPU");
}

unsigned int Zero::Sprite::glId() noexcept { return this->texture.id; }

::PixelFormat Zero::Sprite::format() noexcept { return static_cast<::PixelFormat>(this->texture.format); }

::Texture Zero::Sprite::get() noexcept { return this->texture; }

void Zero::Sprite::draw() noexcept {
  DrawTextureEx(this->texture, this->position, this->rotation, this->scale, this->tint);
}

void Zero::Sprite::render() { this->draw(); }

void Zero::Sprite::render(const Transform2D& transform) {
  // Draw with pro params
  auto sourceRect =
      Rectangle{.x = 0, .y = 0, .width = (float)this->texture.width, .height = (float)this->texture.height};
  auto destRect = Rectangle{.x = transform.position.x,
                            .y = transform.position.y,
                            .width = (float)this->texture.width,
                            .height = (float)this->texture.height};
  auto origin = Vector2{.x = (float)this->texture.width / 2, .y = (float)this->texture.height / 2};
  DrawTexturePro(this->texture, sourceRect, destRect, origin, transform.rotation + this->rotation, this->tint);
}