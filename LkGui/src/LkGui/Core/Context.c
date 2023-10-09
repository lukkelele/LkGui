#include "LkGui/Core/Context.h"
#include "LkGui/LkGui_Internal.h"

LkGuiContext* _LkGui_MainContext;


LkGuiContext* LkGui_CreateContext()
{
    _LkGui_MainContext = LK_NEW(LkGuiContext);
    _LkGui_MainContext->MainWindow = NULL;
    _LkGui_MainContext->BackendData = LK_NEW(LkGui_BackendData);
    _LkGui_MainContext->BackendData->Shaders[0];
    // _LkGui_Context_Init_BackendData(_LkGui_MainContext->BackendData);
    return _LkGui_MainContext;
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


void _LkGui_Context_Init_BackendData(LkGui_BackendData* backendData)
{
    backendData->Shaders[LkGui_ShaderIndex_Normal] = _LkGui_CreateShader(LK_SHADER_PATH_BasicColor);
    backendData->Shaders[LkGui_ShaderIndex_Outline] = _LkGui_CreateShader(LK_SHADER_PATH_Outline);
    backendData->Shaders[LkGui_ShaderIndex_TransformMatrix] = _LkGui_CreateShader(LK_SHADER_PATH_TransformMatrix);
}
