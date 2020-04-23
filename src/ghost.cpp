#include "ghost.h"


Ghost::Ghost(std::string modelPath, std::string texturePath, glm::vec3 position, glm::vec3 color) : position(position), color(color) {
  model = std::unique_ptr<Model>(new Model());
  model->load(modelPath, texturePath);
}

void Ghost::update(float dt) {
  animation += dt;
  if (animation >= 0.7) {
    this->position = glm::vec3(this->path[0].first, 0.0f, this->path[0].second);
    this->path.erase(path.begin());
    animation = 0;
  }
}

void Ghost::draw(Shader shader, int index) {
  shader.use();
  shader.setPointLight(this->position, this->color, index);
  model->draw(this->position, 0.2, -180, shader);
}