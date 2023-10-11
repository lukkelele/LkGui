#include "LkGui.h"


LkGuiContext* LkGui_MainContext;

//=============================================================================
// [SECTION] LkGui API
//=============================================================================
LkGuiContext* LkGui_CreateContext()
{
    LkGui_MainContext = LK_NEW(LkGuiContext);
    LkGui_MainContext->MainViewport = NULL;
    LkGui_MainContext->MainWindow = NULL;
    LkGui_MainContext->BackendData = LK_NEW(LkGui_BackendData);
    LkGui_MainContext->BackendData->Shaders[0];

    return LkGui_MainContext;
}

void LkGui_Init()
{
    _LkGui_Context_Init_BackendData(LkGui_MainContext->BackendData);
    // Initiate geometry collection
    LkGui_MainContext->GeometryStorage = LK_NEW(LkGui_GeometryStorage);
    LkGui_GeometryStorage* geo_storage = LkGui_MainContext->GeometryStorage;
    geo_storage->Rectangle = LK_NEW(LkGui_Rectangle);
    LkGui_Rectangle* rect = geo_storage->Rectangle;
    rect->VA = _LkGui_CreateVertexArray();
    rect->VB = _LkGui_CreateVertexBuffer(_LkGui_Geometry_Box_Vertices_NoTex, LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex));
    rect->IB = _LkGui_CreateIndexBuffer(_LkGui_Geometry_Box_Indices, 6);
    rect->VertexBufferSize = LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex);
    printf("Rect vertexbuffersize: %d\n", rect->VertexBufferSize);
    _LkGui_VertexArray_AddBuffer(rect->VA, rect->VB, LkGui_VertexBufferLayout_VertCoords);
    LK_ASSERT(rect->VB);
    LK_ASSERT(rect->IB);
}

LkGuiContext* LkGui_GetContext()
{
    if (LkGui_MainContext == NULL)
    {
        printf("You need to create a LkGui context before using any other functions! Call LkGui_CreateContext()\n");
        exit(1);
    }
    return LkGui_MainContext;
}


void _LkGui_Context_Init_BackendData(LkGui_BackendData* backendData)
{
    backendData->Shaders[LkGui_ShaderIndex_Normal] = _LkGui_CreateShader(LK_SHADER_PATH_BasicColor);
    backendData->Shaders[LkGui_ShaderIndex_Outline] = _LkGui_CreateShader(LK_SHADER_PATH_Outline);
    backendData->Shaders[LkGui_ShaderIndex_TransformMatrix] = _LkGui_CreateShader(LK_SHADER_PATH_TransformMatrix);
}


//=============================================================================
// [SECTION] File I/O
//=============================================================================
long _LkGui_FileSize(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    return filesize;
}

char* _LkGui_ReadFile(const char* filepath)
{
    FILE *file = fopen(filepath, "rb");
    if (!file)
    {
        fprintf(stderr, "ERROR: fopen %s failed: %d %s\n", filepath, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    int filesize = _LkGui_FileSize(file);
    char *data = calloc(filesize + 1, sizeof(char));
    fread(data, 1, filesize, file);
    fclose(file);
    return data;
}
