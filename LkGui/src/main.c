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

    mat4 identity_mat;
    glm_mat4_identity(identity_mat);

    LkVec2 last_mouse_pos;
    LkVec2 mouse_pos_diff;
    LkGui_Rectangle* rect = ctx->GeometryStorage->Rectangle;
    rect->P1 = LKVEC2(-0.50f, -0.50f);
    rect->P2 = LKVEC2( 0.50f,  0.50f);

    // glm_mat4_identity(rect->Model);
    // memcpy(rect->Model, identity_mat, sizeof(mat4));

    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.10f, 0.80f, 0.60f, 1.0f);
        glm_mat4_identity(rect->Model);

        LkVec2 mouse_pos = LkGui_Mouse_GetPos();
        bool mouse_pressed = LkGui_Mouse_IsButtonPressed(GLFW_MOUSE_BUTTON_1);
        if (mouse_pressed)
            printf("mouse button is pressed\n");
        else
            printf("NOT pressed\n");

        mouse_pos_diff = LKVEC2((mouse_pos.x - last_mouse_pos.x), (mouse_pos.y - last_mouse_pos.y));
        printf("Mouse Coords: (%f, %f), diff: (%f, %f)\n", mouse_pos.x, mouse_pos.y, last_mouse_pos.x, last_mouse_pos.y);

        LkGui_Draw_Rectangle(rect);
        // _LkGui_Draw_Rectangle(rect->P1, rect->P2);
        last_mouse_pos = mouse_pos;

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}
