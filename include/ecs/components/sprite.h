#ifndef ZERO_COMPONENTS_AUDIO_H_
#define ZERO_COMPONENTS_AUDIO_H_

#include <raylib.h>

#include <filesystem>

#include "ecs/components/transform.h"

namespace Zero {
  class Sprite {
    public:
      Sprite(const std::string& fileName) noexcept;
      ~Sprite() noexcept;
      unsigned int glId() noexcept;
      ::PixelFormat format() noexcept;
      ::Texture2D get() noexcept;
      void draw() noexcept;
      void render();
      void render(const Transform2D&);

      ::Vector2 position;
      float rotation;
      float scale;
      ::Color tint;

    private:
      const static std::filesystem::path assetDir;
      std::string filePath;
      ::Texture2D texture;
  };
}  // namespace Zero

#endif