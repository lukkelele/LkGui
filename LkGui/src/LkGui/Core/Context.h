#ifndef LKGUI_CONTEXT_H
#define LKGUI_CONTEXT_H
//==============================================================================
// LkContext
//==============================================================================
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "LkGui/Core/Base.h"
#include "LkGui/Backends/LkGui_Impl_Base.h"

typedef struct LkGuiContext LkGuiContext;

struct LkGuiContext
{
    void*               MainWindow;
    LkGui_BackendData*  BackendData;
};

//==============================================================================
// Internal
//------------------------------------------------------------------------------

//==============================================================================

void LkGui_CreateContext();
LkGuiContext* LkGui_GetContext();


#endif // LKGUI_CONTEXT_H
