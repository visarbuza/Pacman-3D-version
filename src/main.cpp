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

#include <iostream>

GLfloat lastX = 400, lastY = 300;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float dt);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// timing
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;

int main() {
  // glfw: initialize and configure
  auto window = initialize_glfw_and_gl(SCR_WIDTH, SCR_HEIGHT);

  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glEnable(GL_DEPTH_TEST);

  // build and compile our shader zprogram
  Shader ourShader("../resources/shaders/vertex.vert", "../resources/shaders/fragment.frag");

  auto pinky = Model();
  pinky.load("resources/models/ghost.obj", "resources/textures/ghost_texture_pink.png");

  auto inky = Model();
  inky.load("resources/models/ghost.obj", "resources/textures/ghost_texture_blue.png");

  auto clyde = Model();
  clyde.load("resources/models/ghost.obj", "resources/textures/ghost_texture_orange.png");

  auto blinky = Model();
  blinky.load("resources/models/ghost.obj", "resources/textures/ghost_texture_red.png");

  ourShader.use();

  // render loop
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // activate shader
    ourShader.use();
    ourShader.setVec3("spotLight.position", camera.Position);
    ourShader.setVec3("spotLight.direction", camera.Front);
    ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    ourShader.setVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
    ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    ourShader.setFloat("spotLight.constant", 1.0f);
    ourShader.setFloat("spotLight.linear", 0.09);
    ourShader.setFloat("spotLight.quadratic", 0.032);
    ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(5.0f)));
    ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(7.0f)));

    pinky.draw(glm::vec3(0.0f, 0.f, 0.0f), -90, camera.GetViewMatrix());
    inky.draw(glm::vec3(1.0f, 0.f, 0.0f), -90, camera.GetViewMatrix());
    clyde.draw(glm::vec3(0.0f, 0.f, 1.0f), -90, camera.GetViewMatrix());
    blinky.draw(glm::vec3(1.0f, 0.f, 1.0f), -90, camera.GetViewMatrix());

    processInput(window, deltaTime);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

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