#ifndef LKGUI_CONTEXT_H
#define LKGUI_CONTEXT_H
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
//==============================================================================
// LkContext
//==============================================================================

typedef struct LkContext LkContext;

struct LkContext
{
    void* MainWindow;
};

//==============================================================================
// Internal
//------------------------------------------------------------------------------
static void LkGui_Init_MainContext();

//==============================================================================

LkContext* LkGui_GetContext();


#endif // LKGUI_CONTEXT_H
