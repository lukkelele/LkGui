#ifndef LKGUI_H
#define LKGUI_H

#include "LkGui_Internal.h"

//=============================================================================
// [SECTION] Declarations
//=============================================================================
typedef struct LkGuiContext    LkGuiContext;

struct LkGuiContext
{
    void*                   MainViewport;
    void* 					MainWindow;
    void*                   GlfwWindowHandle;
    LkGui_BackendData*      BackendData; // move GlfwHandle here ?
    LkGeometryStorage*      GeometryStorage;
    LkVec2                  WindowSize;
    LkVec2                  ViewportSize;

    LkVec2                  MousePos;
    LkVec2                  LastMousePos;
    LkVec2                  MousePosDiff;
};

//=============================================================================
// [SECTION] Context
//=============================================================================
LkGuiContext* LkGui_CreateContext();
void          LkGui_Init(); // Run after backends are setup
LkGuiContext* LkGui_GetContext();

//=============================================================================
// [SECTION] Internal
//=============================================================================
static void   LkGui_InitBackendData(LkGui_BackendData* backend_data);
static void   LkGui_InitGeometryStorage(LkGeometryStorage* geometry_storage);

//=============================================================================
// [SECTION] Geometry
//=============================================================================
void LkGui_CreateRectangle(LkVec2 p1, LkVec2 p2);



#endif // LKGUI_H
