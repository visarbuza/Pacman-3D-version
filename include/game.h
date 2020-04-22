#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "level.h"
#include "camera.h"


class Game {
  public:
    GLboolean keys[1024];
    void init();
    void update(float dt);
    void processInput(float dt);
    void render(Shader& shader);
    Camera camera = Camera(glm::vec3(-1.0f, 0.0f, 13.0f));
  private:
    std::vector<Model> characters;
    Level level;
    
};

#endif