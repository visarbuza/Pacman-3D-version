#include "model.h"

#include <gfx.h>
#include <glad/glad.h>
#include <tiny_obj_loader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>

/** Constants for vertex attribute locations */
constexpr auto va_position = 0;
constexpr auto va_normal = 1;
constexpr auto va_texcoord = 2;

/** Constants for texture sampler bindings */
constexpr auto tb_diffuse = 0;

Model::~Model() noexcept
{
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
  glDeleteVertexArrays(1, &m_vao);
}

Model::Model(Model &&other)
    : m_vbo(other.m_vbo),
      m_ebo(other.m_ebo),
      m_vao(other.m_vao),
      m_texture(std::move(other.m_texture)),
      m_index_count(other.m_index_count)
{
  other.m_vbo = 0u;
  other.m_ebo = 0u;
  other.m_vao = 0u;
  other.m_index_count = 0u;
}

Model &Model::operator=(Model &&other)
{
  /** Protect */
  if (this == &other)
  {
    return *this;
  }

  /** Destroy */
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
  glDeleteVertexArrays(1, &m_vao);

  /** Steal */
  m_vbo = other.m_vbo;
  m_ebo = other.m_ebo;
  m_vao = other.m_vao;
  m_texture = std::move(other.m_texture);
  m_index_count = other.m_index_count;

  /** Clean */
  other.m_vbo = 0u;
  other.m_ebo = 0u;
  other.m_vao = 0u;
  other.m_index_count = 0u;

  return *this;
}

void Model::load(const std::string &filepath_obj, const std::string &diffuse_path)
{
  m_texture.load_texture(diffuse_path);

  /** Load OBJ Data */
  tinyobj::attrib_t attributes{};
  std::vector<tinyobj::shape_t> shapes{};
  std::vector<tinyobj::material_t> materials{};
  std::string warning{}, error{};

  if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, filepath_obj.c_str()))
  {
    GFX_ERROR("Could not load model: W(%s) E(%s)", warning.c_str(), error.c_str());
  }

  /** Success loading, so we can extract data here */
  std::vector<Vertex> out_vertices{};
  std::vector<unsigned> out_indices{};
  for (const auto &shape : shapes)
  {
    for (const auto &index : shape.mesh.indices)
    {
      /** Uses non-deal index loading, this does not remove duplicate vertices, it's naive, but works for demo purposes
       */
      out_vertices.push_back({});
      out_indices.push_back(out_indices.size());

      auto &vertex = out_vertices.back();
      vertex.position = {attributes.vertices[3 * index.vertex_index + 0],
                         attributes.vertices[3 * index.vertex_index + 1],
                         attributes.vertices[3 * index.vertex_index + 2]};

      vertex.normals = {attributes.normals[3 * index.normal_index + 0], attributes.normals[3 * index.normal_index + 1],
                        attributes.normals[3 * index.normal_index + 2]};

      vertex.texcoord = {attributes.texcoords[2 * index.texcoord_index + 0],
                         attributes.texcoords[2 * index.texcoord_index + 1]};
    }
  }

  /** Set index count */
  m_index_count = out_indices.size();

  /** Create VAO / VBO / EBO */
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * out_vertices.size(), out_vertices.data(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * out_indices.size(), out_indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(va_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
  glVertexAttribPointer(va_normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normals));
  glVertexAttribPointer(va_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texcoord));

  glEnableVertexAttribArray(va_position);
  glEnableVertexAttribArray(va_normal);
  glEnableVertexAttribArray(va_texcoord);

  GFX_INFO("Loaded model %s (%u vertices).", filepath_obj.c_str(), out_vertices.size());
}

void Model::draw(glm::vec3 position, float rotation, Shader shader)
{
  auto model = glm::translate(glm::mat4(1.f), position);
  model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
  model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
  auto normal_matrix = glm::mat3(model);

  shader.setMat4("model", model);
  shader.setMat3("normal_matrix", normal_matrix);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBindVertexArray(m_vao);

  m_texture.bind(tb_diffuse);
  glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
}
