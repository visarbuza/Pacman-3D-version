#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Simple texture manager with basic caching to prevent reloads
 */
class Texture {
 private:
  /** Loaded texture GL Handles and paths */
  uint32_t m_handle{};

 public:
  ~Texture() noexcept;
  Texture(Texture&& other) noexcept;
  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;
  Texture& operator=(Texture&& other) noexcept;
  Texture() = default;

  /**
   * Load a single texture and return handle
   *
   * @param filepath Path to texture
   * @return OpenGL handle to texture
   */
  void load_texture(const std::string& filepath);

  /**
   * Bind the texture at the given slot
   *
   * @param binding Binding slot to bind
   * @note Only bindings 0-15 are guaranteed to exist
   */
  void bind(uint32_t binding);

  /**
   * Implicit conversion so we can use in place of OpenGL handles
   */
  operator uint32_t();
};
