#ifdef LK_IMPL_OPENGL_GLAD
#include <glad/glad.h>
#endif
#include "LkGui.h"
#include "LkGui_Impl_Glfw.h"


struct LkGui_ShaderProgramSource
{
    const char* VertexSource;
    const char* FragmentSource;
};

enum LkGui_ShaderType
{
    LkGui_ShaderType_None     = -1,
    LkGui_ShaderType_Vertex   =  0,
    LkGui_ShaderType_Fragment =  1,
};


//=============================================================================
// [SECTION] Renderer
//=============================================================================
bool _LkGui_GLCall(const char* function, const char* file, int line)
{
    unsigned int error;
    while ((error = glGetError()))
    {
        printf("[OpenGL Error] (%d)\nFUNCTION: %s\nFILE: %s\n LINE: %d", error, function, file, line);
        return false;
    }
    return true;
}

void _LkGui_GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

void _LkGui_Draw(LkGui_VertexArray* va, LkGui_IndexBuffer* ib, LkGui_Shader* shader)
{
    _LkGui_Shader_Bind(shader);
    _LkGui_VertexArray_Bind(va);
    _LkGui_IndexBuffer_Bind(ib);
    LK_GLCALL(glDrawElements(GL_TRIANGLES, _LkGui_IndexBuffer_GetCount(ib), GL_UNSIGNED_INT, NULL));
}

void _LkGui_Draw_NoIB(LkGui_VertexArray* va, LkGui_Shader* shader)
{
    _LkGui_Shader_Bind(shader);
    _LkGui_VertexArray_Bind(va);
    LK_GLCALL(glDrawArrays(GL_TRIANGLES, 0, LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex) / LK_2D_VERTEX_SIZE));
}

LkGui_VertexArray* _LkGui_CreateVertexArray()
{
    // unsigned int va;
    LkGui_VertexArray* va = LK_NEW(LkGui_VertexArray);
    glGenVertexArrays(1, &va->ID);
    _LkGui_VertexArray_Bind(va);
    return va;
}

LkGui_VertexBuffer* _LkGui_CreateVertexBuffer(float* _vertices, unsigned int _arrsize)
{
    LkGui_VertexBuffer* vb = LK_NEW(LkGui_VertexBuffer);
    glGenBuffers(1, &vb->ID);
    glBindBuffer(GL_ARRAY_BUFFER, vb->ID);
    glBufferData(GL_ARRAY_BUFFER, _arrsize * sizeof(float), _vertices, GL_STATIC_DRAW);
    return vb;
}

void _LkGui_VertexArray_AddBuffer(LkGui_VertexArray* va, LkGui_VertexBuffer* vb, unsigned int elements_per_vertex/*== LkGui_VertexBufferLayout enum*/)
{
    // TODO: Struct to hold relevant data for vaos and vbos + layouts
    LkGui_VertexBufferLayout* layout = LK_NEW(LkGui_VertexBufferLayout);
    _LkGui_VertexBufferLayout_Init(layout);
    _LkGui_VertexBufferLayout_Push_Float(layout, elements_per_vertex);

    _LkGui_VertexArray_Bind(va);
    _LkGui_VertexBuffer_Bind(vb);
    unsigned int offset = 0;
    LkGui_VertexBufferElement* elements = layout->Elements;

    for (unsigned int i = 0; i < layout->ElementCount; i++)
    {
        LkGui_VertexBufferElement element = elements[i];
        glEnableVertexAttribArray(i);
        unsigned int stride = _LkGui_VertexBufferLayout_GetStride(layout);
        glVertexAttribPointer(i, element.Count, element.Type, element.Normalized, stride, (const void*)offset);
        offset += element.Count * _LkGui_VertexBufferElement_GetSizeOfType(element.Type);
    }
    free(layout);
}

void _LkGui_VertexArray_Bind(LkGui_VertexArray* va)
{
    // printf("va->ID == %d\n", va->ID);
    glBindVertexArray(va->ID);
}

void _LkGui_VertexBuffer_Bind(LkGui_VertexBuffer* vb)
{
    glBindBuffer(GL_ARRAY_BUFFER, vb->ID);
}

void _LkGui_VertexArray_Unbind(LkGui_VertexArray* va)
{
    glBindVertexArray(0);
}

void _LkGui_VertexBuffer_Unbind(LkGui_VertexBuffer* vb)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int _LkGui_VertexBufferElement_GetSizeOfType(unsigned int type)
{
    switch (type)
    {
        case GL_FLOAT:         return 4;
        case GL_UNSIGNED_INT:  return 4;
        case GL_UNSIGNED_BYTE: return 1;
    }
    return 0;
}

void _LkGui_VertexBufferLayout_Init(LkGui_VertexBufferLayout* layout)
{
    layout->ElementCount = 0;
    layout->Stride = 0;
}

unsigned int _LkGui_VertexBufferLayout_GetStride(LkGui_VertexBufferLayout* layout)
{
    return layout->Stride;
}

void _LkGui_VertexBufferLayout_Push_Float(LkGui_VertexBufferLayout* layout, unsigned int count)
{
    LkGui_VertexBufferElement element = {GL_FLOAT, count, GL_FALSE};
    layout->Elements[layout->ElementCount++] = element;
    layout->ElementCount += count;
    layout->Stride += count * _LkGui_VertexBufferElement_GetSizeOfType(GL_FLOAT);
}

LkGui_IndexBuffer* _LkGui_CreateIndexBuffer(const void* data, unsigned int count)
{
    LK_ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    LkGui_IndexBuffer* ib = LK_NEW(LkGui_IndexBuffer);
    glGenBuffers(1, &ib->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    ib->Count = count;
    return ib;
}

void _LkGui_IndexBuffer_Bind(LkGui_IndexBuffer* ib)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->ID);
}

void _LkGui_IndexBuffer_Unbind(unsigned int id)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int _LkGui_IndexBuffer_GetCount(LkGui_IndexBuffer* ib)
{
    return ib->Count;
}

void _LkGui_DeleteBuffer(unsigned int id)
{
    glDeleteBuffers(1, &id);
}

//=============================================================================
// [SECTION] Shaders
//=============================================================================
void _LkGui_Shader_Bind(LkGui_Shader* shader)
{
    glUseProgram(shader->ID);
}

void _LkGui_Shader_Unbind(LkGui_Shader* shader)
{
    glUseProgram(0);
}

LkGui_ShaderProgramSource _LkGui_ParseShader(const char* filepath)
{
    // printf("Parsing shader: %s\n", filepath);
    FILE* file = fopen(filepath, "r");
    if (!file)
    {
        char errBuf[240];
        sprintf(errBuf, "[LkGui] Failed to open shader file: '%s'", filepath);
        perror(errBuf);
        exit(EXIT_FAILURE);
    }

    const size_t BUFSIZE = 600;
    char line[BUFSIZE];
    char vertexBuffer[4096] = {0};
    char fragmentBuffer[4096] = {0};
    char* currentBuffer = NULL;

    while (fgets(line, BUFSIZE, file))
    {
        // printf("%s", line);
        if (strstr(line, "#shader vertex") != NULL)
            currentBuffer = vertexBuffer;
        else if (strstr(line, "#shader fragment") != NULL)
            currentBuffer = fragmentBuffer;
        else if (currentBuffer)
            strncat(currentBuffer, line, BUFSIZE - 1);
    }

    fclose(file);

    LkGui_ShaderProgramSource source;
    source.VertexSource = strdup(vertexBuffer);
    source.FragmentSource = strdup(fragmentBuffer);

    return source;
}

unsigned int _LkGui_CheckShaderCompilation(unsigned int shader_id, LkGui_ShaderType type)
{
    int res;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(shader_id, length, &length, message);
        printf("Failed to compile %s shader!\n%s", type == LkGui_ShaderType_Vertex ? "Vertex" : "Fragment", message);
        glDeleteShader(shader_id);
        return LK_ERROR;
    }
    return res;
}

unsigned int _LkGui_CompileShader(const char* source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    printf("Creating shader source (glShaderSource)\n");
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    unsigned int shader_result = _LkGui_CheckShaderCompilation(id, type);
    if (shader_result == GL_FALSE)
    {
        printf("Errors occured when compiling shader, exiting");
        exit(EXIT_FAILURE);
    }

    return id;
}

LkGui_Shader* _LkGui_CreateShader(const char* filepath)
{
    LkGui_ShaderProgramSource source = _LkGui_ParseShader(filepath);
    unsigned int program = glCreateProgram();
    unsigned int vs = _LkGui_CompileShader(source.VertexSource, GL_VERTEX_SHADER);
    unsigned int fs = _LkGui_CompileShader(source.FragmentSource, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    LkGui_Shader* shader = LK_NEW(LkGui_Shader);
    shader->ID = program;
    free((void*)source.VertexSource);
    free((void*)source.FragmentSource);
    return shader;
}

void _LkGui_Shader_SetUniform1f(LkGui_Shader* shader, const char* loc, float val)
{
    LK_GLCALL(glUniform1f(glGetUniformLocation(shader->ID, loc), val));
}

void _LkGui_Shader_SetUniform1u(LkGui_Shader* shader, const char* loc, unsigned int val)
{
    LK_GLCALL(glUniform1ui(glGetUniformLocation(shader->ID, loc), val));
}

// TODO: Cache uniform locations
void _LkGui_Shader_SetUniformMat4f(LkGui_Shader* shader, const char* loc, mat4 mat)
{
    _LkGui_Shader_Bind(shader);
    int u_loc = glGetUniformLocation(shader->ID, loc);// 1, GL_FALSE, (GLfloat*)mat);
    // printf("Shader mat4f, u_loc == %d\n", u_loc);
    if (u_loc == GL_INVALID_VALUE) printf("u_loc == INVALID VALUE\n");
    LK_GLCALL(glUniformMatrix4fv(u_loc, 1, GL_FALSE, (GLfloat*)mat));
}

LkGui_Shader* _LkGui_GetShader(int shader_idx)
{
    LkGuiContext* ctx = LkGui_GetContext();
    return ctx->BackendData->Shaders[shader_idx];
}

//=============================================================================
// [SECTION] Drawing geometry
//=============================================================================
void LkGui_Draw_Rectangle(LkRectangle* rect)
{
    glm_mat4_identity(rect->Model); // temporary fix
    LkVec2 p1, p2;
    p1 = rect->P1;
    p2 = rect->P2;
    // Follow cursor with rectangle
    LkVec2 mouse_pos_translation = LkGui_Mouse_GetPos();
    _LkGui_Matrix_Translate(rect->Model, mouse_pos_translation);

    LkGuiContext* ctx = LkGui_GetContext();
    LK_ASSERT_RECTANGLE(rect);
    LkGui_Shader* transform_shader = _LkGui_GetShader(LkGui_ShaderIndex_TransformMatrix);
    _LkGui_Shader_Bind(transform_shader);
    _LkGui_Shader_SetUniformMat4f(transform_shader, "u_TransformMatrix", rect->Model);
    _LkGui_IndexBuffer_Bind(rect->IB);
    _LkGui_VertexArray_Bind(rect->VA);
    LK_GLCALL(glDrawElements(GL_TRIANGLES, _LkGui_IndexBuffer_GetCount(rect->IB), GL_UNSIGNED_INT, NULL));
}

void _LkGui_Draw_Rectangle(LkVec2 p1, LkVec2 p2)
{
    // mat4 transformMatrix;
    // glm_mat4_identity(transformMatrix);
    // _LkGui_Math_Transform_Rectangle(p1, p2, transformMatrix);

    // LkGuiContext* ctx = LkGui_GetContext();
    // LkRectangle* rect = ctx->GeometryStorage->Rectangle;
    // LK_ASSERT(rect != NULL);
    // LK_ASSERT(rect->VA != NULL);
    // LK_ASSERT(rect->VB != NULL);
    // LK_ASSERT(rect->IB != NULL);
    // // _LkGui_Shader_Bind(_LkGui_GetShader(LkGui_ShaderIndex_Normal));
    // LkGui_Shader* transform_shader = _LkGui_GetShader(LkGui_ShaderIndex_TransformMatrix);
    // _LkGui_Shader_Bind(transform_shader);
    // // _LkGui_Shader_SetUniformMat4f(transform_shader, "u_TransformMatrix", identity_mat);
    // _LkGui_Shader_SetUniformMat4f(transform_shader, "u_TransformMatrix", transformMatrix);
    // _LkGui_IndexBuffer_Bind(rect->IB);
    // _LkGui_VertexArray_Bind(rect->VA);
    // LK_GLCALL(glDrawElements(GL_TRIANGLES, _LkGui_IndexBuffer_GetCount(rect->IB), GL_UNSIGNED_INT, NULL));
}

void _LkGui_Draw_AddOutline(float thickness)
{
    LkGuiContext* ctx = LkGui_GetContext();
    LkGui_Shader* outline_shader = ctx->BackendData->Shaders[LkGui_ShaderIndex_Outline];
    _LkGui_Shader_Bind(outline_shader);
    glLineWidth(thickness);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    _LkGui_Shader_Unbind(outline_shader);
}

//=============================================================================
// [SECTION] Keyboard and Mouse
//=============================================================================
bool LkGui_Mouse_IsButtonPressed(int mouse_code)
{
    LkGuiContext* ctx = LkGui_GetContext();
    LK_ASSERT(ctx->GlfwWindowHandle);
    int button_state = glfwGetMouseButton(ctx->GlfwWindowHandle, mouse_code);
    return button_state == GLFW_PRESS;
}

LkVec2 LkGui_Mouse_GetPos()
{
    LkGuiContext* ctx = LkGui_GetContext();
    LK_ASSERT(ctx->GlfwWindowHandle);
    double x, y;
    glfwGetCursorPos(ctx->GlfwWindowHandle, &x, &y);
    LkVec2 pos = { x, y };
    return pos;
}

float LkGui_Mouse_GetX()
{
    LkVec2 pos = LkGui_Mouse_GetPos();
    return pos.x;
}

float LkGui_Mouse_GetY()
{
    LkVec2 pos = LkGui_Mouse_GetPos();
    return pos.y;
}

//=============================================================================
// [SECTION] Mathematics
//=============================================================================
void _LkGui_Math_Transform_Rectangle(LkVec2 p1, LkVec2 p2, mat4 mat)
{
    _LkGui_Matrix_Translate(mat, LKVEC2(1200.0f, 600.0f));
    _LkGui_Matrix_Scale(mat, 0.50f);
}

void _LkGui_Matrix_Scale(mat4 mat, float scaler)
{
    glm_scale(mat, (vec3){scaler, scaler, scaler});
}

// In pixel coordinates
void _LkGui_Matrix_Translate(mat4 mat, LkVec2 translation)
{
    LkVec2 translation_ndc = _LkGui_Math_ConvertToNDC(translation);
    glm_translate(mat, (vec3){translation_ndc.x, translation_ndc.y, 0.0f});
}

LkVec2 _LkGui_Math_ConvertToNDC(LkVec2 pixel_coords)
{
    LkGuiContext* ctx = LkGui_GetContext();
    LkVec2 windowSize = ctx->WindowSize;
    LkVec2 ndc_coords;
    ndc_coords.x = (2.0f * pixel_coords.x) / windowSize.x - 1.0f;
    ndc_coords.y = 1.0f - (2.0f * pixel_coords.y) / windowSize.y;
    // printf("coords (%f, %f) --> ndc.x == %f, ndc.y == %f\n", pixel_coords.x, pixel_coords.y, ndc_coords.x, ndc_coords.y);
    return ndc_coords;
}

// TODO: add format message here with variadic args
void _LkGui_Print_LkVec2(LkVec2 vec)
{
    printf("LkVec2: (%f, %f)\n", vec.x, vec.y);
}



//=============================================================================
// [SECTION] Geometry
//=============================================================================
float _LkGui_Geometry_Box_Vertices_NoTex[8] = {
   -0.5f, -0.5f,  // 0
    0.5f, -0.5f,  // 1
    0.5f,  0.5f,  // 2
   -0.5f,  0.5f   // 3
};

float _LkGui_Geometry_Box_Vertices_NoTex_NoIb[12] = {
   -0.5f, -0.5f,
    0.5f, -0.5f,
   -0.5f,  0.5f,

   -0.5f,  0.5f,
    0.5f, -0.5f,
    0.5f,  0.5f
};

unsigned int _LkGui_Geometry_Box_Indices[6] = {
    0, 1, 2,
    2, 3, 0
};
