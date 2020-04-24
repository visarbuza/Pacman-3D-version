#include "level.h"

void Level::load() {
  readLevel("resources/levels/level0");
  cube.load("resources/models/cube.obj", "resources/textures/wall.png");
  foodModel.load("resources/models/cube.obj", "resources/textures/food.jpg");
}

void Level::draw(Shader shader) {
  drawFloor(shader);
  for (auto const &item : grid) {
    if (item.second) {
      cube.draw(glm::vec3(item.first.first, 0.0f, item.first.second), 0.5, 0, shader);
      cube.draw(glm::vec3(item.first.first, 1.0f, item.first.second), 0.5, 0, shader);
    }
  }

  for (auto &food : foodGrid) {
    if (food.isVisible) {
      food.draw(&foodModel, shader);
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
      cube.draw(glm::vec3(x - 15, -1.0, z - 14), 0.5, 0, shader);
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
          foodGrid.push_back(Food(glm::vec3(x, -0.35, z), 0.04, 0));
        }

        z++;
      }
      z = -14;
      x++;
      std::cout << std::endl;
    }
  }
}