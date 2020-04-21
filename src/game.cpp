#include "game.h"

void Game::init() {
  pinky.load("resources/models/ghost.obj", "resources/textures/ghost_texture_pink.png");  
  inky.load("resources/models/ghost.obj", "resources/textures/ghost_texture_blue.png");
  blinky.load("resources/models/ghost.obj", "resources/textures/ghost_texture_red.png");
  clyde.load("resources/models/ghost.obj", "resources/textures/ghost_texture_orange.png");
  
}

void Game::update() {

}

void Game::render(Shader shader) {
  shader.use();

  
  pinky.draw(glm::vec3(0.0f, 0.f, 0.0f), -90, shader);
  inky.draw(glm::vec3(1.0f, 0.f, 0.0f), -90, shader);
  blinky.draw(glm::vec3(1.0f, 0.f, 1.0f), -90, shader);
  clyde.draw(glm::vec3(0.0f, 0.f, 1.0f), -90, shader);
}