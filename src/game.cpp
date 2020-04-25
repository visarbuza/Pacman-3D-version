#include "game.h"

void Game::init() {
  shader = Shader("../resources/shaders/vertex.vert", "../resources/shaders/fragment.frag");

  state = GAME_MENU;
  level.load();

  text = TextRenderer(Config::SCR_WIDTH, Config::SCR_HEIGHT);
  text.load("resources/fonts/ocraext.TTF", 24);

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
                               glm::vec3(0.0, 0.0f, 1 - i), glm::vec3(1.0, 1.0, 0.0)));
        break;
    }
  }

  for (auto &ghost: ghosts) {
    int start[2] = {(int)ghost.getPosition().x, (int)ghost.getPosition().z};
    int end[2] = {-1, 13};
    ghost.path = route.search(level.grid, start, end);
  }

  score = 0;
}

void Game::update(float dt) {
  if (level.update(camera.Position.x, camera.Position.z)) score++;
  for (auto &ghost: ghosts) {
    ghost.update(dt);
  }
}

void Game::processInput(float dt) {}

void Game::render() {
  shader.reset();
  setLighting();
  setUpTransformations();
  
  auto i = 0;
  for (auto& ghost : ghosts) {
    ghost.draw(shader, i);
    i++;
  }
  displayScore();
  level.draw(shader);
}

void Game::setUpTransformations() {
  auto projection = glm::perspective(glm::radians(50.f), 16.f / 9.f, 0.01f, 650.f);
  shader.setMat4("view", camera.GetViewMatrix());
  shader.setMat4("projection", projection);
}

void Game::setLighting() {
  shader.setDirLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.0f), glm::vec3(0.35f), glm::vec3(0.5f));
  shader.setSpotLight(camera.Position, camera.Front);
  shader.toggleFlashlight(flashlight);
}

void Game::displayScore() {
  std::stringstream ss;
  ss << this->score;
  text.renderText("Score: " + ss.str(), 5.0f, 5.0f, 1.0);
}