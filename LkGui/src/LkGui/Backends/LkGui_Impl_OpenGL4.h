#ifndef LKGUI_IMPL_OPENGL4
#define LKGUI_IMPL_OPENGL4

#include <ctype.h>
#include <stdbool.h>

#ifdef LK_IMPL_OPENGL_GLAD
#include <glad/glad.h>
#endif


typedef struct LkGui_ImplOpenGL4_Data LkGui_ImplOpenGL4_Data;

struct LkGui_ImplOpenGL4_Data
{
    bool VSyncEnabled;
    bool DepthEnabled;
    bool CullingEnabled;
    bool BlendingEnabled;
    bool LineSmooth;
};

//==============================================================================
// Internal
//------------------------------------------------------------------------------
static void _LkGui_ImplOpenGL4_InitStruct();
//==============================================================================

unsigned int LkGui_ImplOpenGL4_Init();
// Blending
void LkGui_ImplOpenGL4_SetBlending(int blending);
void LkGui_ImplOpenGL4_EnableBlending();
void LkGui_ImplOpenGL4_DisableBlending();
// Depth
void LkGui_ImplOpenGL4_SetDepth(int depth);
void LkGui_ImplOpenGL4_EnableDepth();
void LkGui_ImplOpenGL4_DisableDepth();
// Line
void LkGui_ImplOpenGL4_SetLineAntiAliasing(int enabled);
void LkGui_ImplOpenGL4_EnableLineAntiAliasing();
void LkGui_ImplOpenGL4_DisableLineAntiAliasing();


#endif // LKGUI_IMPL_OPENGL4
