#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <util.h>
#include <camera.h>
#include <model.h>
#include <shader.h>
#include <config.h>
#include <game.h>

#include <iostream>

GLfloat lastX = 400, lastY = 300;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float dt);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);

// settings


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

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


  // build and compile our shader zprogram
  Shader mainShader("../resources/shaders/vertex.vert", "../resources/shaders/fragment.frag");

  auto game = Game();
  game.init();

  mainShader.use();

  // render loop
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // render
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // activate shader
    mainShader.use();
    mainShader.setVec3("spotLight.position", camera.Position);
    mainShader.setVec3("spotLight.direction", camera.Front);
    mainShader.setVec3("spotLight.ambient", 0.1f, 0.1f, 0.1f);
    mainShader.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f);
    mainShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    mainShader.setFloat("spotLight.constant", 1.0f);
    mainShader.setFloat("spotLight.linear", 0.09);
    mainShader.setFloat("spotLight.quadratic", 0.032);
    mainShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    mainShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    auto view = camera.GetViewMatrix();
    auto projection = glm::perspective(glm::radians(45.f), 16.f / 9.f, 0.01f, 650.f);

    mainShader.setMat4("view", view);
    mainShader.setMat4("projection", projection);


    game.render(mainShader);

    if (Config::devMode) {
      draw_gui();
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
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, dt);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, dt);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, dt);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, dt);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) { camera.ProcessMouseMovement(xPos, yPos); }

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }