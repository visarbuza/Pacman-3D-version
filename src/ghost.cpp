#include "ghost.h"
#include <iostream>

Ghost::Ghost(std::string modelPath, std::string texturePath, glm::vec3 position, glm::vec3 color, float searchTime)
    : position(position), nextPosition(position), front(glm::vec3(-1.0f, 0.0f, 0.0f)), color(color), searchTime(searchTime) {
  model = std::unique_ptr<Model>(new Model());
  model->load(modelPath, texturePath);
  rotation = 180;
}

void Ghost::update(float dt) {
  if (path.size() == 0) {
    return;
  }

  float velocity = speed * dt;
  if (glm::distance(position, nextPosition) <= 0.09) {
    nextPosition = glm::vec3(path[1].first, 0.0f, path[1].second);
    direction = glm::normalize(nextPosition - position);
    rotate();
    front = direction;
    path.erase(path.begin());
  }
  position += front * velocity;
}

void Ghost::draw(Shader shader, int index) {
  shader.use();
  shader.setGhostLight(this->position, this->color, index);
  model->draw(this->position, 0.2, rotation, shader);
}

void Ghost::rotate() {
  crossProduct = glm::cross(front, direction);
  dotProduct = glm::dot(front, direction);
  
  if (crossProduct.y < 0) {
    rotation += glm::degrees(glm::acos(dotProduct)) * (-1);
  } else {
    rotation += glm::degrees(glm::acos(dotProduct));
  }
  rotation = rotation % 360;
}