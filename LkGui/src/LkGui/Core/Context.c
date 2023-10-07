#include "LkGui/Core/Context.h"

LkContext _LkMainContext;


void LkGui_Init_MainContext()
{
    _LkMainContext.MainWindow = NULL;
}

LkContext* LkGui_GetContext()
{
    return &_LkMainContext;
}
