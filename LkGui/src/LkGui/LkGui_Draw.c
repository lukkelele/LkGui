#include "LkGui.h"
#include "LkGui_Internal.h"


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
void _LkGui_Draw(unsigned int va, LkGui_IndexBuffer* ib, unsigned int shader)
{
    _LkGui_Shader_Bind(shader);
    _LkGui_VertexArray_Bind(va);
    _LkGui_IndexBuffer_Bind(ib->ID);
    // printf("IndexBuffer: %d, count: %d\n", ib->ID, ib->Count);
    // printf("GetCount(ib->ID) == %d\n", _LkGui_IndexBuffer_GetCount(ib));
    LK_GLCALL(glDrawElements(GL_TRIANGLES, _LkGui_IndexBuffer_GetCount(ib), GL_UNSIGNED_INT, NULL));
}

void _LkGui_Draw_NoIB(unsigned int va, unsigned int shader)
{
    _LkGui_Shader_Bind(shader);
    _LkGui_VertexArray_Bind(va);
    LK_GLCALL(glDrawArrays(GL_TRIANGLES, 0, LK_ARRAYSIZE(_LkGui_Geometry_Box_Vertices_NoTex) / LK_2D_VERTEX_SIZE));
}

unsigned int _LkGui_CreateVertexArray()
{
    // unsigned int* va = (unsigned int*)malloc(sizeof(unsigned int));
    unsigned int va;
    glGenVertexArrays(1, &va);
    _LkGui_VertexArray_Bind(va);
    return va;
}

unsigned int _LkGui_CreateVertexBuffer(float* _vertices, unsigned int _arrsize)
{
    unsigned int vb;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, _arrsize * sizeof(float), _vertices, GL_STATIC_DRAW);
    return vb;
}

void _LkGui_VertexArray_AddBuffer(unsigned int va, unsigned int vb, unsigned int elements_per_vertex/*== LkGui_VertexBufferLayout enum*/)
{
    // TODO: Struct to hold relevant data for vaos and vbos + layouts
    LkGui_VertexBufferLayout* layout = LK_NEW(LkGui_VertexBufferLayout);
    _LkGui_VertexBufferLayout_Init(layout);
    _LkGui_VertexBufferLayout_Push_Float(layout, elements_per_vertex);

    _LkGui_VertexArray_Bind(va);
    _LkGui_VertexBuffer_Bind(vb);
    unsigned int offset = 0;
    LkGui_VertexBufferElement* elements = layout->Elements;
    // printf("Elements in layout: %d\n", elements->Count);

    for (unsigned int i = 0; i < layout->ElementCount; i++)
    {
        // printf("Element %d\n", i);
        LkGui_VertexBufferElement element = elements[i];
        glEnableVertexAttribArray(i);
        unsigned int stride = _LkGui_VertexBufferLayout_GetStride(layout);
        glVertexAttribPointer(i, element.Count, element.Type, element.Normalized, stride, (const void*)offset);
        offset += element.Count * _LkGui_VertexBufferElement_GetSizeOfType(element.Type);
    }
    free(layout);
}

void _LkGui_VertexArray_Bind(unsigned int _id)
{
    glBindVertexArray(_id);
}

void _LkGui_VertexBuffer_Bind(unsigned int _id)
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void _LkGui_VertexArray_Unbind(unsigned int _id)
{
    glBindVertexArray(0);
}

void _LkGui_VertexBuffer_Unbind(unsigned int _id)
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

void _LkGui_IndexBuffer_Bind(unsigned int id)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
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
void _LkGui_Shader_Bind(unsigned int id)
{
    glUseProgram(id);
}

void _LkGui_Shader_Unbind(unsigned int id)
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

unsigned int _LkGui_CreateShader(const char* filepath)
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

    free((void*)source.VertexSource);
    free((void*)source.FragmentSource);

    return program;
}

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
