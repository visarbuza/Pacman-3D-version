#include "ghost.h"
#include <iostream>

Ghost::Ghost(std::string modelPath, std::string texturePath, glm::vec3 position, glm::vec3 color)
    : position(position), nextPosition(position), front(glm::vec3(-1.0f, 0.0f, 0.0f)), color(color) {
  model = std::unique_ptr<Model>(new Model());
  model->load(modelPath, texturePath);
  rotation = 180;
}

void Ghost::update(float dt) {
  float velocity = speed * dt;
  if (path.size() == 0) {
    return;
  }
  if (glm::distance(position, nextPosition) <= 0.09) {
    nextPosition = glm::vec3(path[1].first, 0.0f, path[1].second);
    direction = glm::normalize(nextPosition - position);
    glm::vec3 cross = glm::cross(front, direction);
    float dot = glm::dot(front, direction);
    if (cross.y < 0) {
      rotation += glm::degrees(glm::acos(dot)) * (-1);
    } else {
      rotation += glm::degrees(glm::acos(dot));
    }
    rotation = rotation % 360;
    front = direction;
    path.erase(path.begin());
  }
  position += front * velocity;
}

void Ghost::draw(Shader shader, int index) {
  shader.use();
  shader.setPointLight(this->position, this->color, index);
  model->draw(this->position, 0.2, rotation, shader);
}