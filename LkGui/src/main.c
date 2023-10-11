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
    // _LkGui_Context_Init_BackendData(ctx->BackendData); /* Needs to be run AFTER OpenGL instantiation */

    LkGui_VertexArray* va;
    LkGui_VertexBuffer* vb;
    LkGui_IndexBuffer* ib;
    va = _LkGui_CreateVertexArray();
    vb = _LkGui_CreateVertexBuffer(_LkGui_Geometry_Box_Vertices_NoTex, LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex));
    ib = _LkGui_CreateIndexBuffer(_LkGui_Geometry_Box_Indices, 6);
    _LkGui_VertexArray_AddBuffer(va, vb, LkGui_VertexBufferLayout_VertCoords);

    LkGui_Shader* shader = _LkGui_GetShader(LkGui_ShaderIndex_Normal);
    LkGui_Shader* outline_shader = _LkGui_GetShader(LkGui_ShaderIndex_Outline);

    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.10f, 0.80f, 0.60f, 1.0f);

        _LkGui_Shader_Bind(shader);
        _LkGui_VertexArray_Bind(va);
        _LkGui_IndexBuffer_Bind(ib);
        LkVec2 p1 = {1, 0};
        LkVec2 p2 = {2, 1};
        _LkGui_Draw_Rectangle(p1, p2);

        _LkGui_Draw(va, ib, shader);
        _LkGui_Draw_AddOutline(10.0f);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}
