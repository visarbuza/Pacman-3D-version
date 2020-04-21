#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "model.h"

class Game {
  public:
    void init();
    void update();
    void render(Shader shader);
  private:
    Model inky;
    Model pinky;
    Model blinky;
    Model clyde;
};

#endif