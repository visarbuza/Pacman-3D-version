#include "level.h"

void Level::load() {
  readLevel("resources/levels/level0");
  cube.load("resources/models/cube.obj", "resources/textures/wall.png");
}

void Level::draw(Shader shader) {
  drawFloor(shader);
}

void Level::drawFloor(Shader shader) {
  shader.use();
  for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 28; j++) {
      cube.draw(glm::vec3(i - 15, -1.0, j - 14), 0.5, 0, shader);
    }
  }
}

void Level::readLevel(const std::string& path){
  std::string line;
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::cout << line << std::endl;
    }
  }
}