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

    unsigned int shader = _LkGui_CreateShader("assets/shaders/simple.shader");

    printf("Box[2] %f\n", _LkGui_Geometry_Box_Vertices_NoTex[2]);

    unsigned int va, vb;

    va = _LkGui_CreateVertexArray();
    vb = _LkGui_CreateVertexBuffer(_LkGui_Geometry_Box_Vertices_NoTex, LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex));
    _LkGui_VertexArray_AddBuffer(va, vb, LkGui_VertexBufferLayout_VertCoords);

    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.10f, 0.80f, 0.60f, 1.0f);

        // Use our shader
        glUseProgram(shader);

        // Bind VAO and draw the box
        glBindVertexArray(va);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}
