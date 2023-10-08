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

#define LK_NO_ERROR 0
#define LK_ERROR    1

#define LK_UNUSED(_VAR)        ((void)(_VAR))
#define LK_ASSERT(_EXPR)       assert(_EXPR)
#define LK_ARRAYSIZE(_ARR)     ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define LK_NEW(_TYPE)          (_TYPE*)malloc(sizeof(_TYPE))

#define LKGUI_MAX_VERTEXBUFFERLAYOUT_SIZE 200

//=============================================================================
// [SECTION] Forward declarations
//=============================================================================
typedef struct LkGui_ShaderProgramSource  LkGui_ShaderProgramSource;
typedef struct LkGui_VertexBufferElement  LkGui_VertexBufferElement;
typedef struct LkGui_VertexBufferLayout   LkGui_VertexBufferLayout;
typedef enum LkGui_ShaderType          LkGui_ShaderType;
typedef enum LkGui_VertexBufferLayout_ LkGui_VertexBufferLayout_;

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

enum LkGui_VertexBufferLayout_
{
    LkGui_VertexBufferLayout_None          = 0,
    LkGui_VertexBufferLayout_VertCoords    = 2,
    LkGui_VertexBufferLayout_VertTexCoords = 4,
};

//=============================================================================
// [SECTION] File I/O
//=============================================================================
long _LkGui_FileSize(FILE* file);
char* _LkGui_ReadFile(const char* filepath);


//=============================================================================
// [SECTION] Renderer
//=============================================================================
unsigned int _LkGui_CreateVertexArray();
unsigned int _LkGui_CreateVertexBuffer(float* _vertices, unsigned int _arrsize);
// void         _LkGui_VertexArray_AddBuffer(unsigned int va, unsigned int vb, LkGui_VertexBufferLayout* layout);
void         _LkGui_VertexArray_AddBuffer(unsigned int va, unsigned int vb, unsigned int layout);
void         _LkGui_VertexArray_Bind(unsigned int id);
void         _LkGui_VertexBuffer_Bind(unsigned int id);
void         _LkGui_VertexArray_Unbind(unsigned int id /* could be skipped but for verbose purposes let stay */);
void         _LkGui_VertexBuffer_Unbind(unsigned int id);
unsigned int _LkGui_VertexBufferElement_GetSizeOfType(unsigned int type);
void         _LkGui_VertexBufferLayout_Init(LkGui_VertexBufferLayout* layout);
void         _LkGui_VertexBufferLayout_Push_Float(LkGui_VertexBufferLayout* layout, unsigned int count);
unsigned int _LkGui_VertexBufferLayout_GetStride(LkGui_VertexBufferLayout* layout);

//=============================================================================
// [SECTION] Shaders
//=============================================================================
unsigned int              _LkGui_Shader_Bind(unsigned int id);
unsigned int              _LkGui_Shader_Unbind(unsigned int id);
unsigned int              _LkGui_CreateShader(const char* filepath);
unsigned int              _LkGui_CompileShader(const char* source, unsigned int type);
static unsigned int       _LkGui_CheckShaderCompilation(unsigned int shader_id, LkGui_ShaderType type);
LkGui_ShaderProgramSource _LkGui_ParseShader(const char* filepath);



//=============================================================================
// [SECTION] Geometry Data
//=============================================================================
extern float _LkGui_Geometry_Box_Vertices_NoTex[12];

#endif // LKGUI_INTERNAL_H
