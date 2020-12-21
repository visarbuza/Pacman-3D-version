#include "game.h"

void Game::init() {
    state = GAME_MENU;
    shader = Shader("./resources/shaders/vertex.vert", "./resources/shaders/fragment.frag");
    text = TextRenderer(Config::SCR_WIDTH, Config::SCR_HEIGHT);
    text.load("resources/fonts/ocraext.TTF", 24);

    level.load();
    player.load("./resources/models/sphere.obj", "./resources/textures/food.jpg");

    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                ghosts.push_back(Ghost(i, "./resources/models/ghost.obj", "./resources/textures/ghost_texture_pink.png",
                                       glm::vec3(-1.0, 0.0f, 1 - i), glm::vec3(1.0, 0.08, 0.5), 2.0f));
                break;
            case 1:
                ghosts.push_back(Ghost(i, "./resources/models/ghost.obj", "./resources/textures/ghost_texture_red.png",
                                       glm::vec3(-1.0, 0.0f, 1 - i), glm::vec3(1.0, 0.0, 0.0), 3.0f));
                break;
            case 2:
                ghosts.push_back(Ghost(i, "./resources/models/ghost.obj", "./resources/textures/ghost_texture_blue.png",
                                       glm::vec3(-1.0, 0.0f, 1 - i), glm::vec3(0.0, 0.0, 1.0), 4.0f));
                break;
            case 3:
                ghosts.push_back(Ghost(i, "./resources/models/ghost.obj",
                                       "./resources/textures/ghost_texture_orange.png", glm::vec3(-1.0, 0.0f, 1 - i),
                                       glm::vec3(1.0, 1.0, 0.0), 5.0f));
                break;
        }
    }
    score = 0;
}

void Game::update(float dt) {
    if (score == 320) state = GAME_WIN;  // Hard coded cuz I'm lazy :)
    checkCollision(dt);
    if (level.update(camera.Position.x, camera.Position.z)) score++;

    for (auto &ghost : ghosts) {
        ghost.deltaTime += dt;
        if (ghost.deltaTime >= ghost.searchTime) {
            ghost.deltaTime = 0;
            int start[2] = {(int)ghost.getPosition().x, (int)ghost.getPosition().z};
            int end[2] = {(int)camera.Position.x, (int)camera.Position.z};
            //ghost.path = route.search(level.grid, start, end);
        }
        ghost.update(dt);
        if (glm::distance(ghost.getPosition(), camera.Position) < 0.32f) state = GAME_LOSS;
    }
}

void Game::processInput(float dt) {
    if (keys[GLFW_KEY_W]) camera.ProcessKeyboard(FORWARD, dt);
    if (keys[GLFW_KEY_S]) camera.ProcessKeyboard(BACKWARD, dt);
    if (keys[GLFW_KEY_A]) camera.ProcessKeyboard(LEFT, dt);
    if (keys[GLFW_KEY_D]) camera.ProcessKeyboard(RIGHT, dt);
    if (keys[GLFW_KEY_F]) flashlight = !flashlight;
    if (keys[GLFW_KEY_M]) view = (view + 1) % 3;
    if (keys[GLFW_KEY_LEFT_SHIFT]) {
        camera.ProcessKeyboard(RUN, dt);
    } else {
        camera.ProcessKeyboard(STOP_RUN, dt);
    }
}

void Game::render() {
    shader.reset();
    setLighting();
    setUpTransformations();

    for (auto &ghost : ghosts) {
        ghost.draw(shader);
    }
    level.draw(shader);
    drawPlayer();

    displayScore();
}

void Game::renderEndScreen() {
    std::stringstream ss;
    ss << score;

    if (state == GAME_WIN) {
        text.renderText("You win!", 320.0, Config::SCR_HEIGHT / 2 - 20.0, 1.0);
    } else {
        text.renderText("You lose!", 320.0, Config::SCR_HEIGHT / 2 - 20.0, 1.0);
    }

    text.renderText("Score:" + ss.str(), 325.0, Config::SCR_HEIGHT / 2, 1.0);
}

void Game::setUpTransformations() {
    auto projection = glm::perspective(glm::radians(50.f), 16.f / 9.f, 0.01f, 650.f);
    auto lookAt = glm::mat4(1.0f);

    switch (view) {
        case FIRST_PERSON:
            lookAt = camera.GetFirstPersonView();
            break;
        case THIRD_PERSON:
            lookAt = camera.GetThirdPersonView();
            break;
        case BIRD_VIEW:
            lookAt = camera.Get2DView();
            break;
    }

    shader.setMat4("view", lookAt);
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

void Game::checkCollision(float dt) {
    for (auto &tile : level.grid) {
        if (tile.second) {
            if (glm::distance(camera.Position, glm::vec3(tile.first.first, 0.0f, tile.first.second)) <= 0.7) {
                if (keys[GLFW_KEY_W]) camera.ProcessKeyboard(BACKWARD, dt);
                if (keys[GLFW_KEY_S]) camera.ProcessKeyboard(FORWARD, dt);
                if (keys[GLFW_KEY_A]) camera.ProcessKeyboard(RIGHT, dt);
                if (keys[GLFW_KEY_D]) camera.ProcessKeyboard(LEFT, dt);
            }
        }
    }
}

void Game::drawPlayer() {
    if (view != FIRST_PERSON) {
        player.draw(camera.Position, 0.06, 0, shader);
    }
}
