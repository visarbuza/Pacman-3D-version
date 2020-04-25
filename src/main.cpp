#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <util.h>
#include <camera.h>
#include <model.h>
#include <shader.h>
#include <game.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float dt);
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
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  game.init();

  // render loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (game.state == GAME_MENU || game.state == GAME_PAUSED) {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      ImGui::Begin("Menu");
      const char* text = game.state == GAME_MENU ? "Play game" : "Resume game";
      if (ImGui::Button(text)) {
        game.state = GAME_ACTIVE;
      }
      if (ImGui::Button("Exit")) {
				glfwSetWindowShouldClose(window, GL_TRUE);
      }
      ImGui::End();
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    } else {
      game.update(deltaTime);
      game.render();
      if (Config::devMode) {
        draw_gui();
      }
    }

    processInput(window, deltaTime);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window, GLfloat dt) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) game.state = GAME_PAUSED;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) game.camera.ProcessKeyboard(FORWARD, dt);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) game.camera.ProcessKeyboard(BACKWARD, dt);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) game.camera.ProcessKeyboard(LEFT, dt);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) game.camera.ProcessKeyboard(RIGHT, dt);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) game.camera.ProcessKeyboard(RUN, dt);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) game.camera.ProcessKeyboard(STOP_RUN, dt);
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
    if (game.flashlight) {
      game.flashlight = false;
    } else {
      game.flashlight = true;
    }
  }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) { game.camera.ProcessMouseMovement(xPos, yPos); }
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }