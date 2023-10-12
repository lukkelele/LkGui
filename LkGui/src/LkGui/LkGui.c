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
    // Do not run LkGui_Init() in here

    return LkGui_MainContext;
}

void LkGui_Init()
{
    LkGui_InitBackendData(LkGui_MainContext->BackendData);
    LkGui_InitGeometryStorage(LkGui_MainContext->GeometryStorage);
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


void LkGui_InitBackendData(LkGui_BackendData* backendData)
{
    backendData->Shaders[LkGui_ShaderIndex_Normal] = _LkGui_CreateShader(LK_SHADER_PATH_BasicColor);
    backendData->Shaders[LkGui_ShaderIndex_Outline] = _LkGui_CreateShader(LK_SHADER_PATH_Outline);
    backendData->Shaders[LkGui_ShaderIndex_TransformMatrix] = _LkGui_CreateShader(LK_SHADER_PATH_TransformMatrix);
}

void LkGui_InitGeometryStorage(LkGeometryStorage* geometry_storage)
{
    LkGui_MainContext->GeometryStorage = LK_NEW(LkGeometryStorage);
    LkGeometryStorage* geo_storage = LkGui_MainContext->GeometryStorage;
    for (int n = 0; n < LK_ARRAYSIZE(geo_storage->Rectangles); n++)
    {
        geo_storage->Rectangles[n] = NULL;
    }
    // geo_storage->Rectangles = (LkRectangle**)malloc(LK_ARRAYSIZE(geo_storage->Rectangles) * sizeof(LkRectangle*));
    //geo_storage->Rectangles = (LkRectangle**)malloc(50 * sizeof(LkRectangle*));
}

void LkGui_CreateRectangle(LkVec2 p1, LkVec2 p2)
{
    LkGeometryStorage* geometry_storage = LkGui_MainContext->GeometryStorage;
    LK_ASSERT(geometry_storage);
    LK_ASSERT(geometry_storage->Rectangles);
    // printf("LK_ARRAYSIZE(geometry_storage->Rectangles) == %d\n", LK_ARRAYSIZE(geometry_storage->Rectangles)); // prints 100 correctly
    for (int rect_idx = 0; rect_idx < LK_ARRAYSIZE(geometry_storage->Rectangles); rect_idx++)
    {
        LkRectangle* rect = geometry_storage->Rectangles[rect_idx];
        if (!rect || rect_idx < LK_ARRAYSIZE(geometry_storage->Rectangles))
        {
            printf("Creating new rectangle at Rectangles[idx] == %d\n", rect_idx);
            rect = LK_NEW(LkRectangle);
            rect->VA = _LkGui_CreateVertexArray();
            rect->VB = _LkGui_CreateVertexBuffer(_LkGui_Geometry_Box_Vertices_NoTex, LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex));
            rect->IB = _LkGui_CreateIndexBuffer(_LkGui_Geometry_Box_Indices, 6);
            rect->VertexBufferSize = LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex);
            // rect->Model = (mat4*)malloc(sizeof(mat4));
            LK_ASSERT_RECTANGLE(rect);
            _LkGui_VertexArray_AddBuffer(rect->VA, rect->VB, LkGui_VertexBufferLayout_VertCoords);
            glm_mat4_identity(rect->Model);
            geometry_storage->Rectangles[rect_idx] = rect;
            geometry_storage->RectangleCount++;
            return; // Leave function after new rectangle has been created to not continously create new ones
        }
    }
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

