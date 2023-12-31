#include "LkGui/Backends/LkGui_Impl_OpenGL4.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "LkGui.h"

void _LkGui_ImplOpenGL4_InitStruct()
{
}

unsigned int LkGui_ImplOpenGL4_Init()
{
    GLenum err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (err == 0)
    {
        printf("[ERROR] Error occured when initializing glad\n");
        return LK_ERROR;
    }
    printf("[LkGui] OpenGL Version: %s\n", glGetString(GL_VERSION));

    LkGui_ImplOpenGL4_EnableBlending();
    LkGui_ImplOpenGL4_EnableLineAntiAliasing();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    return LK_NO_ERROR;
}

void LkGui_ImplOpenGL4_SetBlending(int blending_enabled)
{
    LkGuiContext* ctx = LkGui_GetContext();
    if (blending_enabled == LK_BLENDING_ENABLE)
    {
        ctx->BackendData->BlendingEnabled = true;
        glEnable(GL_BLEND);
        return;
    }
    glDisable(GL_BLEND);
    ctx->BackendData->BlendingEnabled = false;
}

void LkGui_ImplOpenGL4_EnableBlending()  { LkGui_ImplOpenGL4_SetBlending(LK_BLENDING_ENABLE);  }
void LkGui_ImplOpenGL4_DisableBlending() { LkGui_ImplOpenGL4_SetBlending(LK_BLENDING_DISABLE); }

void LkGui_ImplOpenGL4_SetDepth(int depth_enabled)
{
    LkGuiContext* ctx = LkGui_GetContext();
    if (depth_enabled == LK_DEPTH_ENABLE)
    {
        ctx->BackendData->DepthEnabled = true;
        glEnable(GL_DEPTH_TEST);
        return;
    }
    glDisable(GL_DEPTH_TEST);
    ctx->BackendData->DepthEnabled = false;
}

void LkGui_ImplOpenGL4_EnableDepth()  { LkGui_ImplOpenGL4_SetDepth(LK_DEPTH_ENABLE);  }
void LkGui_ImplOpenGL4_DisableDepth() { LkGui_ImplOpenGL4_SetDepth(LK_DEPTH_DISABLE); }

void LkGui_ImplOpenGL4_SetLineAntiAliasing(int enabled)
{
    LkGuiContext* ctx = LkGui_GetContext();
    if (enabled == LK_LINE_ANTIALIASING_ENABLE)
    {
        ctx->BackendData->LineAntiAliasing = true;
        glEnable(GL_LINE_SMOOTH);
        return;
    }
    glDisable(GL_LINE_SMOOTH);
    ctx->BackendData->LineAntiAliasing = false;
}
void LkGui_ImplOpenGL4_EnableLineAntiAliasing()  { LkGui_ImplOpenGL4_SetLineAntiAliasing(LK_LINE_ANTIALIASING_ENABLE);  }
void LkGui_ImplOpenGL4_DisableLineAntiAliasing() { LkGui_ImplOpenGL4_SetLineAntiAliasing(LK_LINE_ANTIALIASING_DISABLE); }
