#include "texture.h"

#include <algorithm>

#include <gfx.h>
#include <glad/glad.h>
#include <stb_image.h>

Texture::~Texture() noexcept { glDeleteTextures(1, &m_handle); }

Texture::Texture(Texture&& other) noexcept : m_handle(std::move(other.m_handle)) {}

Texture& Texture::operator=(Texture&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  /** Clean and steal */
  glDeleteTextures(1, &m_handle);
  m_handle = std::move(other.m_handle);
  other.m_handle = 0u;

  return *this;
}

void Texture::load_texture(const std::string& filepath) {
  /** Clean up */
  glDeleteTextures(1, &m_handle);

  /** Create */
  uint32_t handle{};
  glGenTextures(1, &handle);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, handle);

  /** Parameters */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  /** Load */
  int x, y;
  stbi_set_flip_vertically_on_load(true);
  auto* pixels = stbi_load(filepath.c_str(), &x, &y, nullptr, STBI_rgb_alpha);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  /** Finalize */
  stbi_image_free(pixels);
  GFX_INFO("Loaded image (%dx%d) from %s.", x, y, filepath.c_str());
  m_handle = handle;
}

void Texture::bind(uint32_t binding) {
  glActiveTexture(GL_TEXTURE0 + binding);
  glBindTexture(GL_TEXTURE_2D, m_handle);
}

Texture::operator uint32_t() { return m_handle; }
