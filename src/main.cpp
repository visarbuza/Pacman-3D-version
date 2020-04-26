#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <util.h>
#include <game.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);

Game game;
// timing
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;

int main(int argc, char *argv[]) {
  if (argc > 1 && (std::string)argv[1] == "dev") {
    Config::devMode = true;
  }

  // glfw: initialize and configure
  auto window = initialize_glfw_and_gl(Config::SCR_WIDTH, Config::SCR_HEIGHT);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  initialize_gui(window);
  
  game.init();

  // render loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (game.state == GAME_ACTIVE) {
      game.processInput(deltaTime);
      game.update(deltaTime);
      game.render();
      draw_gui();
    } else {
      game_menu(game, window);
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
	clean_up(window);
  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) game.state = GAME_PAUSED;
  if (key >= 0 && key < 1024)
    if (action == GLFW_PRESS) {
      game.keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      game.keys[key] = false;
    }
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) { game.camera.ProcessMouseMovement(xPos, yPos); }
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }