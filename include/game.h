#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "text_renderer.h"
#include "route_planner.h"
#include "model.h"
#include "level.h"
#include "camera.h"
#include "ghost.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_PAUSED,
    GAME_WIN,
    GAME_LOSS
};

class Game {
  public:
    unsigned int score;
    RoutePlanner route;
    Camera camera = Camera(glm::vec3(-1.0f, 0.0f, 13.0f));
    GameState state;
    float flashlight = false;
    bool keys[1024];
    void init();
    void update(float dt);
    void processInput(float dt);
    void render();
    void renderEndScreen();
  private:
    float searchTime = 0;
    std::vector<Ghost> ghosts;
    Level level;
    Shader shader;
    TextRenderer text;
    void displayScore();
    void setLighting();
    void setUpTransformations();
    void checkCollision(float dt);
};

#endif