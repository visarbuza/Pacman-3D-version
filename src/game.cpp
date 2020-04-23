#include "game.h"

void Game::init() {
  state = GAME_MENU;
  level.load();

  for (int i = 0; i < 4; i++) {
    switch (i) {
      case 0:
        ghosts.push_back(Ghost("resources/models/ghost.obj", "resources/textures/ghost_texture_pink.png",
                               glm::vec3(-1.0, 0.0f, 1 - i), glm::vec3(1.0, 0.08, 0.5)));
        break;
      case 1:
        ghosts.push_back(Ghost("resources/models/ghost.obj", "resources/textures/ghost_texture_red.png",
                               glm::vec3(-1.0, 0.0f, 1 - i), glm::vec3(1.0, 0.0, 0.0)));
        break;
      case 2:
        ghosts.push_back(Ghost("resources/models/ghost.obj", "resources/textures/ghost_texture_blue.png",
                               glm::vec3(-1.0, 0.0f, 1 - i), glm::vec3(0.0, 0.0, 1.0)));
        break;
      case 3:
        ghosts.push_back(Ghost("resources/models/ghost.obj", "resources/textures/ghost_texture_orange.png",
                               glm::vec3(-1.0, 0.0f, 1 - i), glm::vec3(1.0, 1.0, 0.0)));
        break;
    }
  }
}

void Game::update(float dt) {}

void Game::processInput(float dt) {}

void Game::render(Shader& shader) {
  shader.use();

  auto i = 0;
  for (auto& ghost : ghosts) {
    ghost.draw(shader, i);
    i++;
  }

  level.draw(shader);
}