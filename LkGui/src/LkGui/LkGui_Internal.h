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

#ifdef LKGUI_IMPL_OPENGL_GLAD
    #include <glad/glad.h>
#endif // LKGUI_IMPL_OPENGL_GLAD
#include <cglm/cglm.h>
#include "LkGui/Core/Context.h" // move to LkGui.h

#define LK_NO_ERROR 0
#define LK_ERROR    1

#define LK_UNUSED(_VAR)        ((void)(_VAR))
#define LK_ASSERT(_EXPR)       assert(_EXPR)
#define LK_ARRAYSIZE(_ARR)     ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define LK_NEW(_TYPE)          (_TYPE*)malloc(sizeof(_TYPE))
#define LK_GLCALL(_FUNC)       _LkGui_GLClearError(); _FUNC; LK_ASSERT(_LkGui_GLCall(#_FUNC, __FILE__, __LINE__))

#define LK_2D_VERTEX_SIZE 2
#define LK_3D_VERTEX_SIZE 3
#define LKGUI_MAX_VERTEXBUFFERLAYOUT_SIZE 200

//=============================================================================
// [SECTION] Declarations
//=============================================================================
typedef struct LkGui_VertexBufferElement  LkGui_VertexBufferElement;
typedef struct LkGui_VertexBufferLayout   LkGui_VertexBufferLayout;
typedef struct LkGui_ShaderProgramSource  LkGui_ShaderProgramSource;
typedef struct LkGui_IndexBuffer          LkGui_IndexBuffer;
typedef struct LkGui_DrawData             LkGui_DrawData;
typedef struct LkGui_DrawCommand          LkGui_DrawCommand;
typedef struct LkVec2                     LkVec2;
typedef struct LkVec3                     LkVec3;
typedef struct LkVec4                     LkVec4;
// typedef float  LkVec2[2];
// typedef float  LkVec3[3];
// typedef float  LkVec4[4];
typedef enum LkGui_ShaderType             LkGui_ShaderType;
typedef enum LkGui_VertexBufferLayout_    LkGui_VertexBufferLayout_;

//=============================================================================
// [SECTION] Definitions
//=============================================================================
struct LkGui_VertexBufferElement
{
    unsigned int  Type;
    unsigned int  Count;
    unsigned char Normalized;
};

struct LkGui_VertexBufferLayout
{
    LkGui_VertexBufferElement Elements[LKGUI_MAX_VERTEXBUFFERLAYOUT_SIZE];
    unsigned int ElementCount;
    unsigned int Stride;
};

struct LkGui_IndexBuffer
{
    unsigned int ID;
    unsigned int Count;
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


//=============================================================================
// [SECTION] Renderer
//=============================================================================
void               _LkGui_Draw(unsigned int va, LkGui_IndexBuffer* ib, LkGui_Shader* shader);
void               _LkGui_Draw_NoIB(unsigned int va, LkGui_Shader* shader);
unsigned int       _LkGui_CreateVertexArray();
void               _LkGui_VertexArray_AddBuffer(unsigned int va, unsigned int vb, unsigned int layout);
void               _LkGui_VertexArray_Bind(unsigned int id);
void               _LkGui_VertexArray_Unbind(unsigned int id /* could be skipped but for verbose purposes let stay */);
unsigned int       _LkGui_CreateVertexBuffer(float* _vertices, unsigned int _arrsize);
void               _LkGui_VertexBuffer_Bind(unsigned int id);
void               _LkGui_VertexBuffer_Unbind(unsigned int id);
void               _LkGui_VertexBufferLayout_Init(LkGui_VertexBufferLayout* layout);
void               _LkGui_VertexBufferLayout_Push_Float(LkGui_VertexBufferLayout* layout, unsigned int count);
unsigned int       _LkGui_VertexBufferElement_GetSizeOfType(unsigned int type);
unsigned int       _LkGui_VertexBufferLayout_GetStride(LkGui_VertexBufferLayout* layout);
LkGui_IndexBuffer* _LkGui_CreateIndexBuffer(const void* data, unsigned int count);
void               _LkGui_IndexBuffer_Bind(LkGui_IndexBuffer* ib);
void               _LkGui_IndexBuffer_Unbind(unsigned int id);
unsigned int       _LkGui_IndexBuffer_GetCount(LkGui_IndexBuffer* ib);
void               _LkGui_DeleteBuffer(unsigned int id);
bool               _LkGui_GLCall(const char* function, const char* file, int line);
void               _LkGui_GLClearError();


//=============================================================================
// [SECTION] Shaders
//=============================================================================
void                      _LkGui_Shader_Bind(LkGui_Shader* shader);
void                      _LkGui_Shader_Unbind(LkGui_Shader* shader);
LkGui_Shader*             _LkGui_CreateShader(const char* filepath);
unsigned int              _LkGui_CompileShader(const char* source, unsigned int type);
static unsigned int       _LkGui_CheckShaderCompilation(unsigned int shader_id, LkGui_ShaderType type);
LkGui_ShaderProgramSource _LkGui_ParseShader(const char* filepath);
void                      _LkGui_Shader_SetUniform1f(unsigned int shader_id, const char* loc, float val);
void                      _LkGui_Shader_SetUniform1u(unsigned int shader_id, const char* loc, unsigned int val);
void                      _LkGui_Shader_SetUniformMat4f(unsigned int shader_id, const char* loc, mat4 mat);


//=============================================================================
// [SECTION] Drawing geometry
//=============================================================================
void _LkGui_Draw_Rectangle(LkVec2 p1, LkVec2 p2);
void _LkGui_Draw_AddOutline(float thickness);


//=============================================================================
// [SECTION] Mathematics
//=============================================================================
void _LkGui_Math_Transform_Rectangle(LkVec2 p1, LkVec2 p2, mat4 mat);


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
extern float _LkGui_Geometry_Box_Vertices_NoTex[8];
extern float _LkGui_Geometry_Box_Vertices_NoTex_NoIb[12];
extern float _LkGui_Geometry_Cube_Vertices_NoTex[8 * 3];
extern unsigned int _LkGui_Geometry_Box_Indices[6];
extern unsigned int _LkGui_Geometry_Cube_Indices[36];







#endif // LKGUI_INTERNAL_H
