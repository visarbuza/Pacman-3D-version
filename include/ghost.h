#pragma once
#ifndef GHOST_H
#define GHOST_H

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <memory>

#include "model.h"

class Ghost {
  private:
    std::unique_ptr<Model> model;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 color;
    float velocity;
  public:
    Ghost(std::string modelPath, std::string texturePath, glm::vec3 position, glm::vec3 color);
    void draw(Shader shader, int index);
    
    void setPosition(const glm::vec3 position) {
      this->position = position;
    }
    
    glm::vec3 getPosition() const {
      return this->position;
    }
};

#endif