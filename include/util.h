#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gfx.h>

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
    return window;
}