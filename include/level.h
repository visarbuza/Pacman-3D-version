#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <tuple>
#include <map>

#include "model.h"


class Level {
  public:
    void load();
    void draw(Shader shader);
  private:
    std::map<std::pair<int, int> , bool> grid;
    Model cube;
    void drawFloor(Shader shader);
    void readLevel(const std::string &path);

};

#endif