#ifndef LKGUI_CONTEXT_H
#define LKGUI_CONTEXT_H
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


LkGuiContext* LkGui_CreateContext();
LkGuiContext* LkGui_GetContext();

void _LkGui_Context_Init_BackendData(LkGui_BackendData* backendData);


#endif // LKGUI_CONTEXT_H
