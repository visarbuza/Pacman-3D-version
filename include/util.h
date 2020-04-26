#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gfx.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "config.h"
#include "game.h"

GLFWwindow* initialize_glfw_and_gl(int width, int height)
{ // Initialise GLFW
    if (!glfwInit())
    {
        GFX_ERROR("Failed to initialize GLFW\n");
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // For MacOS
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);  // To allow debug callbacks
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, "Pacman 3D", nullptr, nullptr);
    if (window == nullptr)
    {
        GFX_ERROR("Failed to open GLFW window.\n");
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize Glad
    if (!gladLoadGL())
    {
        GFX_ERROR("Failed to initialize GLAD\n");
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    return window;
}

void initialize_gui(GLFWwindow* window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 430 core");
}

void game_menu(Game& game, GLFWwindow* window) {
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
}

void clean_up(GLFWwindow* window) {
  ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
}

void draw_gui() {
  if (!Config::devMode) {
    return;
  }
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::Begin("Dev Menu");
  if (ImGui::Button("Enable/Disable Flight")) {
    Config::flightEnabled = !Config::flightEnabled;
  }
  if (ImGui::Button("Buttons"))
  {
  }
  if (ImGui::Button("Not Implemented"))
  {
  }
  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}