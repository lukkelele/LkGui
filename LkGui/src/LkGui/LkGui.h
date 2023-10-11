#ifndef LKGUI_H
#define LKGUI_H

#include "LkGui_Internal.h"

//=============================================================================
// [SECTION] Declarations
//=============================================================================
typedef struct LkGuiContext    LkGuiContext;


struct LkGuiContext
{
    void*                   MainWindow;
    LkGui_BackendData*      BackendData;
    LkGui_GeometryStorage*  GeometryStorage;
};

//=============================================================================
// [SECTION] Context
//=============================================================================
LkGuiContext* LkGui_CreateContext();
void          LkGui_Init(); // Run after backends are setup
LkGuiContext* LkGui_GetContext();
void _LkGui_Context_Init_BackendData(LkGui_BackendData* backendData);


#endif // LKGUI_H
