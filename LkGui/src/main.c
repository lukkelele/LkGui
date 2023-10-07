#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//===================================================================
// Core
#include "LkGui/Core/Logger.h"
#include "LkGui/Core/Context.h"
// Backend
#include "LkGui/Backends/LkGui_impl_glfw.h"
#include "LkGui/Backends/LkGui_impl_opengl4.h"
//===================================================================


#define WINDOW_TITLE  "LkGui"
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

int main()
{
    LOG_DEBUG("Hello World\n");

    if (!glfwInit())
        return -1;

    // GLFWwindow* glfwWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    // glfwMakeContextCurrent(glfwWindow);
    // LkGui_ImplGlfw_Init(LK_INSTANT_CALLBACKS);
    LkGui_ImplGlfw_Init(true);
    LkGui_ImplGlfw_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL);
    GLFWwindow* glfwWindow = LkGui_ImplGlfw_GetMainWindow();
    // glfwMakeContextCurrent(glfwWindow);


    LkGui_ImplOpenGL4_Init();
    // GLenum err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // if (err == 0)
    // {
    //     printf("[ERROR] Error starting GLAD");
    //     return -1;
    // }
    // else
    // {
    //     printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    // }

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}
