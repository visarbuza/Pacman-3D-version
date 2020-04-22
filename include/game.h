#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>

#include "model.h"
#include "level.h"


class Game {
  public:
    void init();
    void update();
    void render(Shader& shader);
  private:
    std::vector<Model> characters;
    Level level;
    
};

#endif