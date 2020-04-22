#pragma once
#ifndef FOOD_H
#define FOOD_H

#include "model.h"

class Food {
  public:
    Food(glm::vec3 position, float scale, float rotation);
    void collect();
    void draw(Model* model, Shader shader);
    bool isVisible;
  private:
    glm::vec3 position;
    float scale;
    float rotation;
};

#endif