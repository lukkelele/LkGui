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
    LkGui_CreateContext();
    LkGui_ImplGlfw_Init(true);
    LkGui_ImplGlfw_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL);
    GLFWwindow* glfwWindow = LkGui_ImplGlfw_GetMainWindow();
    LkGui_ImplOpenGL4_Init();

    unsigned int va, vb, shader;
    LkGui_IndexBuffer* ib;
    va = _LkGui_CreateVertexArray();
    vb = _LkGui_CreateVertexBuffer(_LkGui_Geometry_Box_Vertices_NoTex, LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex));
    ib = _LkGui_CreateIndexBuffer(_LkGui_Geometry_Box_Indices, 6);
    _LkGui_VertexArray_AddBuffer(va, vb, LkGui_VertexBufferLayout_VertCoords);


    shader = _LkGui_CreateShader("assets/shaders/simple.shader");

    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.10f, 0.80f, 0.60f, 1.0f);

        _LkGui_Draw(va, ib, shader);
        // _LkGui_Shader_Bind(shader);
        // _LkGui_VertexArray_Bind(va);
        // _LkGui_IndexBuffer_Bind(ib->);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}
