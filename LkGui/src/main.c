#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//===================================================================
// Core
#include "LkGui/Core/Logger.h"
#include "LkGui/Core/Context.h"
// Backend
#include "LkGui/Backends/LkGui_Impl_Glfw.h"
#include "LkGui/Backends/LkGui_Impl_OpenGL4.h"
//===================================================================
#include "LkGui/LkGui_Internal.h"

#define WINDOW_TITLE  "LkGui"
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

int main()
{
    LOG_DEBUG("Hello World\n");

    LkGui_CreateContext();
    LkGui_ImplGlfw_Init(true);
    LkGui_ImplGlfw_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL);
    GLFWwindow* glfwWindow = LkGui_ImplGlfw_GetMainWindow();
    LkGui_ImplOpenGL4_Init();

    unsigned int Shader = LkGui_CreateShader("assets/shaders/basic_color.shader");

    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.10f, 0.80f, 0.60f, 1.0f);


        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}
