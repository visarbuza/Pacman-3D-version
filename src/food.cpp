#include "food.h"

Food::Food(glm::vec3 position, float scale, float rotation) : position(position), scale(scale), rotation(rotation) {
  this->isVisible = true;
}

void Food::collect() {
  this->isVisible = false;
}

void Food::draw(Model* model, Shader shader) {
  if (this->isVisible) {
    model->draw(position, scale, rotation, shader);
  }
}