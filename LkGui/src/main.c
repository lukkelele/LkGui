#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//===================================================================
#include "LkGui/Backends/LkGui_Impl_Glfw.h"
#include "LkGui/Backends/LkGui_Impl_OpenGL4.h"
//===================================================================
#include "LkGui/LkGui.h"
#define WINDOW_TITLE  "LkGui"
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080


int main()
{
    LkGuiContext* ctx = LkGui_CreateContext();
    LkGui_ImplGlfw_Init(true);
    LkGui_ImplGlfw_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL);
    GLFWwindow* glfwWindow = LkGui_ImplGlfw_GetMainWindow();
    LkGui_ImplOpenGL4_Init();
    LkGui_Init();

    LkGui_Shader* shader = _LkGui_GetShader(LkGui_ShaderIndex_Normal);
    LkGui_Shader* outline_shader = _LkGui_GetShader(LkGui_ShaderIndex_Outline);

    LkVec2 last_mouse_pos;
    LkVec2 mouse_pos_diff;
    // LkRectangle* rect = ctx->GeometryStorage->Rectangles[0];
    LkGui_CreateRectangle(LKVEC2(-0.50f, -0.50f), LKVEC2(0.50f, 0.50f));
    LkRectangle* rect = ctx->GeometryStorage->Rectangles[0];
    printf("Rectangle count: %d\n", ctx->GeometryStorage->RectangleCount);

    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.10f, 0.80f, 0.60f, 1.0f);

        LkGui_Draw_Rectangle(rect);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}
