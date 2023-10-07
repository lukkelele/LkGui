#ifndef LKGUI_IMPL_BASE_H
#define LKGUI_IMPL_BASE_H

#include "LkGui/Core/Base.h"

#define LKGUI_NO_INSTANT_CALLBACKS       0
#define LKGUI_INSTANT_CALLBACKS          1
#define LKGUI_BLENDING_DISABLE           0
#define LKGUI_BLENDING_ENABLE            1
#define LKGUI_DEPTH_DISABLE              0
#define LKGUI_DEPTH_ENABLE               1
#define LKGUI_LINE_ANTIALIASING_DISABLE  0
#define LKGUI_LINE_ANTIALIASING_ENABLE   1

typedef struct LkGui_BackendData LkGui_BackendData;
typedef enum LkGui_BlendFunc_    LkGui_BlendFunc_;
typedef int LkGui_BlendFunc;

struct LkGui_BackendData
{
    bool VSyncEnabled;
    bool DepthEnabled;
    bool CullingEnabled;
    bool BlendingEnabled;
    bool LineAntiAliasing;
    bool PointAntiAliasing;
    bool PolygonAntiAliasing;
};

enum LkGui_BlendFunc
{
    LkGui_BlendFunc_None                          = 0,
    LkGui_BlendFunc_SrcAlpha_OneMinusSrcAlpha     = 1 << 0,
    LkGui_BlendFunc_SrcAlpha_OneMinusDistantAlpha = 1 << 1,
};

#endif // LKGUI_IMPL_BASE_H
