#include "level.h"

void Level::load() {
  readLevel("resources/levels/level0");
  cube.load("resources/models/cube.obj", "resources/textures/wall.png");
  foodModel.load("resources/models/cube.obj", "resources/textures/food.jpg");
  lamp.load("resources/models/cube.obj", "resources/textures/lamp.jpg");
}

void Level::draw(Shader shader) {
  drawFloor(shader);
  for (auto const &item : grid) {
    if (item.second) {
      cube.draw(glm::vec3(item.first.first, 0.0f, item.first.second), 1.0, 0, shader);
      cube.draw(glm::vec3(item.first.first, 1.0f, item.first.second), 1.0, 0, shader);
    }
  }

  for (auto &food : foodGrid) {
    if (food.isVisible) {
      food.draw(&foodModel, shader);
    }
  }
  renderLamps(shader);
}

void Level::renderLamps(Shader shader) {
for (int i = 0; i < 4; i++) {
    glm::vec3 position(-14.4f, 1.2f, 12.4);
    switch (i) {
      case 0:
        lamp.draw(position, 0.15, 0, shader);
        shader.setPointLights(position, glm::vec3(1.0f, 0.0f, 0.0f), i);
        break;
      case 1:
        position.z = -13.4;
        lamp.draw(position, 0.15, 0, shader);
        shader.setPointLights(position, glm::vec3(1.0f, 0.0f, 0.0f), i);
        break;
      case 2:
        position.x = 14.4;
        position.z = -13.4;
        lamp.draw(position, 0.15, 0, shader);
        shader.setPointLights(position, glm::vec3(1.0f, 0.0f, 0.0f), i);
        break;
      case 3:
        position.x = 14.4;
        position.z = 12.4;
        lamp.draw(position, 0.15, 0, shader);
        shader.setPointLights(position, glm::vec3(1.0f, 0.0f, 0.0f), i);
        break;
    }
  }
}

bool Level::update(float x, float z) {
  for (auto &food : foodGrid) {
    if (food.isVisible) {
      if (food.position.x > x - 0.2 && food.position.x < x + 0.2 && food.position.z > z - 0.2 && food.position.z < z + 0.2) {
        food.isVisible = false;
        return true;
      }
    }
  }

  return false;
}

void Level::drawFloor(Shader shader) {
  shader.use();
  for (int x = 0; x < 31; x++) {
    for (int z= 0; z < 28; z++) {
      cube.draw(glm::vec3(x - 15, -1.0, z - 14), 1.0, 0, shader);
    }
  }
}

void Level::readLevel(const std::string& path){
  std::string line;
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    int x = -15;
    int z = -14;
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      std::string key, value;
      while (linestream >> key) {
        std::pair<int, int> pair(x, z);
        grid.emplace(pair, (bool)std::stoi(key));

        if (std::stoi(key) == 0) {
          foodGrid.push_back(Food(glm::vec3(x, -0.35, z), 0.1, 0));
        }

        z++;
      }
      z = -14;
      x++;
      std::cout << std::endl;
    }
  }
}