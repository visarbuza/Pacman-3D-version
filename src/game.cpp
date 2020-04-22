#include "game.h"

void Game::init() {
  level.load();

  for (int i = 0; i < 4; i++) {
    characters.push_back(Model());
  }
  
  auto i = 0;
  for (auto &character : characters) {
    switch (i) {
      case 0: character.load("resources/models/ghost.obj", "resources/textures/ghost_texture_pink.png");  break;
      case 1: character.load("resources/models/ghost.obj", "resources/textures/ghost_texture_red.png");  break;
      case 2: character.load("resources/models/ghost.obj", "resources/textures/ghost_texture_blue.png");  break;
      case 3: character.load("resources/models/ghost.obj", "resources/textures/ghost_texture_orange.png");  break;
    }
    i++;
  }
}

void Game::update(float dt) {

}

void Game::processInput(float dt) {
  
}

void Game::render(Shader& shader) {
  shader.use();

  auto i = 0;
  for (auto &character : characters) {
    character.draw(glm::vec3(-1.0, 0.0f, 1 - i), 0.2, -180, shader);
    i++;
  }

  level.draw(shader);
}