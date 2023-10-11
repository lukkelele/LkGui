#ifndef LKGUI_INTERNAL_H
#define LKGUI_INTERNAL_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <cglm/cglm.h>

#define LK_NO_ERROR 0
#define LK_ERROR    1
#define LK_2D_VERTEX_SIZE 2
#define LK_3D_VERTEX_SIZE 3
#define LK_MAX_VERTEXBUFFERLAYOUT_SIZE 200
#define LK_NO_INSTANT_CALLBACKS       0
#define LK_INSTANT_CALLBACKS          1
#define LK_BLENDING_DISABLE           0
#define LK_BLENDING_ENABLE            1
#define LK_DEPTH_DISABLE              0
#define LK_DEPTH_ENABLE               1
#define LK_LINE_ANTIALIASING_DISABLE  0
#define LK_LINE_ANTIALIASING_ENABLE   1
#define LK_MAX_ALLOWED_SHADERS        60
// #define LK_SHADER_PATH_BasicColor        "assets/shaders/basic_color.shader"
#define LK_SHADER_PATH_BasicColor        "assets/shaders/simple.shader"
#define LK_SHADER_PATH_Outline           "assets/shaders/outline.shader"
#define LK_SHADER_PATH_TransformMatrix   "assets/shaders/basic_transform.shader"

// Macros
#define LK_UNUSED(_VAR)               ((void)(_VAR))
#define LK_ASSERT(_EXPR)              assert(_EXPR)
#define LK_ARRAYSIZE(_ARR)            ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define LK_NEW(_TYPE)                 (_TYPE*)malloc(sizeof(_TYPE))
#define LK_GLCALL(_FUNC)              _LkGui_GLClearError(); _FUNC; LK_ASSERT(_LkGui_GLCall(#_FUNC, __FILE__, __LINE__))
#define LK_ASSERT_RECTANGLE(_RECT)    LK_ASSERT(_RECT != NULL); LK_ASSERT(_RECT->VA); LK_ASSERT(_RECT->VB); LK_ASSERT(_RECT->IB)
#define LKVEC2(_x, _y)	              (LkVec2){_x, _y}
#define LKVEC4(_x, _y, _w, _z)	      (LkVec4){_x, _y, _w, _z}

//=============================================================================
// [SECTION] Declarations
//=============================================================================
typedef struct LkGui_VertexArray          LkGui_VertexArray;
typedef struct LkGui_VertexBuffer         LkGui_VertexBuffer;
typedef struct LkGui_IndexBuffer          LkGui_IndexBuffer;
typedef struct LkGui_VertexBufferElement  LkGui_VertexBufferElement;
typedef struct LkGui_VertexBufferLayout   LkGui_VertexBufferLayout;
typedef struct LkGui_ShaderProgramSource  LkGui_ShaderProgramSource;
typedef struct LkGui_DrawData             LkGui_DrawData;
typedef struct LkGui_DrawCommand          LkGui_DrawCommand;
typedef struct LkGui_BackendData          LkGui_BackendData;
typedef struct LkGui_GeometryStorage      LkGui_GeometryStorage;
typedef struct LkGui_Rectangle            LkGui_Rectangle;
typedef struct LkGui_Shader               LkGui_Shader;
typedef struct LkGui_Shaders              LkGui_Shaders;
typedef struct LkVec2                     LkVec2;
typedef struct LkVec3                     LkVec3;
typedef struct LkVec4                     LkVec4;
typedef enum LkGui_ShaderType             LkGui_ShaderType;
typedef enum LkGui_VertexBufferLayout_    LkGui_VertexBufferLayout_;
typedef enum LkGui_ShaderIndex_           LkGui_ShaderIndex_;
typedef enum LkGui_BlendFunc_             LkGui_BlendFunc_;
typedef mat3                              LkMat3;
typedef mat4                              LkMat4;
typedef int                               LkGui_BlendFunc;
typedef int                               LkGui_ShaderIndex;


//=============================================================================
// [SECTION] Definitions
//=============================================================================
struct LkGui_BackendData
{
    bool VSyncEnabled;
    bool DepthEnabled;
    bool CullingEnabled;
    bool BlendingEnabled;
    bool LineAntiAliasing;
    bool PointAntiAliasing;
    bool PolygonAntiAliasing;

    LkGui_Shader* Shaders[20];
};

struct LkGui_VertexArray
{
    unsigned int ID;
};

struct LkGui_VertexBuffer
{
    unsigned int ID;
};

struct LkGui_VertexBufferElement
{
    unsigned int  Type;
    unsigned int  Count;
    unsigned char Normalized;
};

struct LkGui_VertexBufferLayout
{
    LkGui_VertexBufferElement Elements[LK_MAX_VERTEXBUFFERLAYOUT_SIZE];
    unsigned int ElementCount;
    unsigned int Stride;
};

struct LkGui_IndexBuffer
{
    unsigned int ID;
    unsigned int Count;
};

struct LkGui_Shader
{
    unsigned int ID;
};

struct LkGui_Shaders
{
    LkGui_Shader Collection[20];
};

enum LkGui_ShaderIndex_
{
    LkGui_ShaderIndex_Normal          = 0,
    LkGui_ShaderIndex_Outline         = 1,
    LkGui_ShaderIndex_TransformMatrix = 2,
};

struct LkGui_DrawData
{
};

struct LkGui_DrawCommand
{
    unsigned int VAO;
    unsigned int IBO;
    unsigned int Shader;
};

struct LkVec2 { float x, y; };
struct LkVec3 { float x, y, z; };
struct LkVec4 { float x, y, z, w; };

enum LkGui_VertexBufferLayout_
{
    LkGui_VertexBufferLayout_None          = 0,
    LkGui_VertexBufferLayout_VertCoords    = 2,
    LkGui_VertexBufferLayout_VertTexCoords = 4,
};

enum LkGui_BlendFunc
{
    LkGui_BlendFunc_None                          = 0,
    LkGui_BlendFunc_SrcAlpha_OneMinusSrcAlpha     = 1 << 0,
    LkGui_BlendFunc_SrcAlpha_OneMinusDistantAlpha = 1 << 1,
};

//=============================================================================
// [SECTION] Renderer
//=============================================================================
void                  _LkGui_Draw(LkGui_VertexArray* va, LkGui_IndexBuffer* ib, LkGui_Shader* shader);
void                  _LkGui_Draw_NoIB(LkGui_VertexArray* va, LkGui_Shader* shader);
LkGui_VertexArray*    _LkGui_CreateVertexArray();
void                  _LkGui_VertexArray_AddBuffer(LkGui_VertexArray* va, LkGui_VertexBuffer* vb, unsigned int layout);
void                  _LkGui_VertexArray_Bind(LkGui_VertexArray* va);
void                  _LkGui_VertexArray_Unbind(LkGui_VertexArray* va /* could be skipped but for verbose purposes let stay */);
LkGui_VertexBuffer*   _LkGui_CreateVertexBuffer(float* _vertices, unsigned int _arrsize);
void                  _LkGui_VertexBuffer_Bind(LkGui_VertexBuffer* vb);
void                  _LkGui_VertexBuffer_Unbind(LkGui_VertexBuffer* vb);
void                  _LkGui_VertexBufferLayout_Init(LkGui_VertexBufferLayout* layout);
void                  _LkGui_VertexBufferLayout_Push_Float(LkGui_VertexBufferLayout* layout, unsigned int count);
unsigned int          _LkGui_VertexBufferElement_GetSizeOfType(unsigned int type);
unsigned int          _LkGui_VertexBufferLayout_GetStride(LkGui_VertexBufferLayout* layout);
LkGui_IndexBuffer*    _LkGui_CreateIndexBuffer(const void* data, unsigned int count);
void                  _LkGui_IndexBuffer_Bind(LkGui_IndexBuffer* ib);
void                  _LkGui_IndexBuffer_Unbind(unsigned int id);
unsigned int          _LkGui_IndexBuffer_GetCount(LkGui_IndexBuffer* ib);
void                  _LkGui_DeleteBuffer(unsigned int id);
bool                  _LkGui_GLCall(const char* function, const char* file, int line);
void                  _LkGui_GLClearError();


//=============================================================================
// [SECTION] Shaders
//=============================================================================
void                      _LkGui_Shader_Bind(LkGui_Shader* shader);
void                      _LkGui_Shader_Unbind(LkGui_Shader* shader);
LkGui_Shader*             _LkGui_CreateShader(const char* filepath);
unsigned int              _LkGui_CompileShader(const char* source, unsigned int type);
static unsigned int       _LkGui_CheckShaderCompilation(unsigned int shader_id, LkGui_ShaderType type);
LkGui_ShaderProgramSource _LkGui_ParseShader(const char* filepath);
void                      _LkGui_Shader_SetUniform1f(LkGui_Shader* shader, const char* loc, float val);
void                      _LkGui_Shader_SetUniform1u(LkGui_Shader* shader, const char* loc, unsigned int val);
void                      _LkGui_Shader_SetUniformMat4f(LkGui_Shader* shader, const char* loc, mat4 mat);
LkGui_Shader*             _LkGui_GetShader(int shader_idx);

//=============================================================================
// [SECTION] Keyboard and Mouse
//=============================================================================
bool   LkGui_Mouse_IsButtonPressed(int mouse_code);
LkVec2 LkGui_Mouse_GetPos();
float  LkGui_Mouse_GetX();
float  LkGui_Mouse_GetY();


//=============================================================================
// [SECTION] Drawing geometry
//=============================================================================
void LkGui_Draw_Rectangle(LkGui_Rectangle* rect);
void _LkGui_Draw_Rectangle(LkVec2 p1, LkVec2 p2);
void _LkGui_Draw_AddOutline(float thickness);
void _LkGui_Print_LkVec2(LkVec2 vec);

//=============================================================================
// [SECTION] Mathematics
//=============================================================================
void _LkGui_Math_Transform_Rectangle(LkVec2 p1, LkVec2 p2, mat4 mat); // FIXME
// 2D Matrix operations
void _LkGui_Matrix_Scale(mat4 mat, float scaler);
void _LkGui_Matrix_Translate(mat4 mat, LkVec2 translation); // Uses pixel coordinates
LkVec2 _LkGui_Math_ConvertToNDC(LkVec2 pixelCoords);


//=============================================================================
// [SECTION] File I/O
//=============================================================================
long _LkGui_FileSize(FILE* file);
char* _LkGui_ReadFile(const char* filepath);


//=============================================================================
// [SECTION] Geometry
//
// Index buffers need to be 'unsigned int', won't work otherwise
//=============================================================================

struct LkGui_GeometryStorage
{
    LkGui_Rectangle* Rectangle;
};

struct LkGui_Rectangle
{
    LkVec2              P1; // Lower diagonal vertex
    LkVec2              P2; // Higher diagonal vertex
    LkGui_VertexArray*  VA;
    LkGui_VertexBuffer* VB;
    LkGui_IndexBuffer*  IB;
    unsigned int        VertexBufferSize;
    LkVec2              Translation;
    LkVec2              Scale;
    LkMat4              Model;
    LkMat4*             _Model;
    LkMat4              ModelViewProjection;
};


extern float _LkGui_Geometry_Box_Vertices_NoTex[8];
extern float _LkGui_Geometry_Box_Vertices_NoTex_NoIb[12];
extern float _LkGui_Geometry_Cube_Vertices_NoTex[8 * 3];
extern unsigned int _LkGui_Geometry_Box_Indices[6];
extern unsigned int _LkGui_Geometry_Cube_Indices[36];







#endif // LKGUI_INTERNAL_H
