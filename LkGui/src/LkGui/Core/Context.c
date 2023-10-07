#include "LkGui/Core/Context.h"

LkGuiContext* _LkGui_MainContext;


void LkGui_CreateContext()
{
    _LkGui_MainContext = LK_NEW(LkGuiContext);
    _LkGui_MainContext->MainWindow = NULL;
    _LkGui_MainContext->BackendData = LK_NEW(LkGui_BackendData);
}

LkGuiContext* LkGui_GetContext()
{
    if (_LkGui_MainContext == NULL)
    {
        printf("You need to create a LkGui context before using any other functions! Call LkGui_CreateContext()\n");
        exit(1);
    }
    return _LkGui_MainContext;
}
