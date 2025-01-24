#ifndef ZERO_TEXTURES_H_
#define ZERO_TEXTURES_H_

#include <raylib.h>

#include <filesystem>
#include <string>

namespace Zero {
  /**
   * Class to handle loading and unloading 2D textures into memory. Zero::Texture2D will handle
   * the understanding of the "assets" directory under the hood. So to load a new texture
   * simple pass the fileName to the constructor.
   */
  class Texture2D {
    public:
      Texture2D() = delete;
      Texture2D(const Texture2D&) = delete;
      Texture2D& operator=(const Texture2D&) = delete;
      Texture2D(const std::string& fileName) noexcept;
      ~Texture2D() noexcept;
      unsigned int id() noexcept;
      ::PixelFormat format() noexcept;
      ::Texture2D get() noexcept;
      void draw() noexcept;

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