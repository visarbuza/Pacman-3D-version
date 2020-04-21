#pragma once

#include "texture.h"
#include "shader.h"

#include <cstdint>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

/**
 * Represents a single model
 */
class Model {
 private:
  uint32_t m_vbo{};
  uint32_t m_ebo{};
  uint32_t m_vao{};
  Texture m_texture{};

  uint32_t m_index_count;

 public:
  ~Model() noexcept;
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;
  Model(Model&& other);
  Model& operator=(Model&& other);
  Model() = default;

  /**
   * The vertex type used by a model
   */
  struct Vertex {
    glm::vec3 position{};
    glm::vec3 normals{};
    glm::vec2 texcoord{};
  };

  /**
   * The filepath to the obj file
   *
   * @param filepath_obj The path to the obj file
   * @param diffuse_path The path to the diffuse texture
   */
  void load(const std::string& filepath_obj, const std::string& diffuse_path);

  void draw(glm::vec3 position, float rotation, Shader shader);
};
