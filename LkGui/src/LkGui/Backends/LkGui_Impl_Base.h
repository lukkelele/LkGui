#ifndef LKGUI_IMPL_BASE_H
#define LKGUI_IMPL_BASE_H

#include "LkGui/Core/Base.h"

#define LK_NO_INSTANT_CALLBACKS       0
#define LK_INSTANT_CALLBACKS          1
#define LK_BLENDING_DISABLE           0
#define LK_BLENDING_ENABLE            1
#define LK_DEPTH_DISABLE              0
#define LK_DEPTH_ENABLE               1
#define LK_LINE_ANTIALIASING_DISABLE  0
#define LK_LINE_ANTIALIASING_ENABLE   1
#define LK_MAX_ALLOWED_SHADERS        60
#define LK_SHADER_PATH_BasicColor        "assets/shaders/basic_color.shader"
#define LK_SHADER_PATH_Outline           "assets/shaders/outline.shader"
#define LK_SHADER_PATH_TransformMatrix   "assets/shaders/basic_transform.shader"

typedef struct LkGui_BackendData LkGui_BackendData;
typedef struct LkGui_Shader      LkGui_Shader;
typedef struct LkGui_Shaders     LkGui_Shaders;
typedef enum LkGui_ShaderIndex_  LkGui_ShaderIndex_;
typedef enum LkGui_BlendFunc_    LkGui_BlendFunc_;
typedef int LkGui_BlendFunc;
typedef int LkGui_ShaderIndex;

enum LkGui_ShaderIndex_
{
    LkGui_ShaderIndex_Normal          = 0,
    LkGui_ShaderIndex_Outline         = 1,
    LkGui_ShaderIndex_TransformMatrix = 2,
};

struct LkGui_Shader
{
    unsigned int ID;
};

struct LkGui_Shaders
{
    LkGui_Shader Collection[LK_MAX_ALLOWED_SHADERS];
};

struct LkGui_BackendData
{
    bool VSyncEnabled;
    bool DepthEnabled;
    bool CullingEnabled;
    bool BlendingEnabled;
    bool LineAntiAliasing;
    bool PointAntiAliasing;
    bool PolygonAntiAliasing;

    LkGui_Shader* Shaders[LK_MAX_ALLOWED_SHADERS];
};

enum LkGui_BlendFunc
{
    LkGui_BlendFunc_None                          = 0,
    LkGui_BlendFunc_SrcAlpha_OneMinusSrcAlpha     = 1 << 0,
    LkGui_BlendFunc_SrcAlpha_OneMinusDistantAlpha = 1 << 1,
};

#endif // LKGUI_IMPL_BASE_H
