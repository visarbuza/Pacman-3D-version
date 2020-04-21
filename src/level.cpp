#include "level.h"

void Level::load() {
  readLevel("resources/levels/level0");
  cube.load("resources/models/cube.obj", "resources/textures/wall.png");
}

void Level::draw(Shader shader) {
  drawFloor(shader);
  for (auto const &item : grid) {
    if (item.second) {
      cube.draw(glm::vec3(item.first.first, 0.0f, item.first.second), 0.5, 0, shader);
      cube.draw(glm::vec3(item.first.first, 1.0f, item.first.second), 0.5, 0, shader);
    }
  }
}

void Level::drawFloor(Shader shader) {
  shader.use();
  for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 28; j++) {
      cube.draw(glm::vec3(j - 14, -1.0, i - 15), 0.5, 0, shader);
    }
  }
}

void Level::readLevel(const std::string& path){
  std::string line;
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    int y = -15;
    int x = -14;
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      std::string key, value;
      while (linestream >> key) {
        std::pair<int, int> pair(x, y);
        grid.emplace(pair, (bool)std::stoi(key));
        x++;
      }
      x = -14;
      y++;
      std::cout << std::endl;
    }
  }
}