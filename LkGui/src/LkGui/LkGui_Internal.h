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
#include <glad/glad.h> /* OpenGL dependency for now, need to rewrite the shader compilation in the future */

#define LK_NO_ERROR 0
#define LK_ERROR    1

#define LK_UNUSED(_VAR)        ((void)(_VAR))
#define LK_ASSERT(_EXPR)       assert(_EXPR)
#define LK_ARRAYSIZE(_ARR)     ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define LK_NEW(_TYPE)          (_TYPE*)malloc(sizeof(_TYPE))

typedef enum LkGui_ShaderType LkGui_ShaderType;
typedef struct LkGui_ShaderProgramSource LkGui_ShaderProgramSource;

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


long _LkGui_FileSize(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    return filesize;
}

char* _LkGui_ReadFile(const char* filepath) {
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

LkGui_ShaderProgramSource _LkGui_ParseShader(const char* filepath)
{
    printf("Parsing shader: %s\n", filepath);
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
        printf("%s", line);
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

static unsigned int _LkGui_CheckShaderCompilation(unsigned int shader_id, LkGui_ShaderType type)
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

unsigned int LkGui_CreateShader(const char* filepath)
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


#endif // LKGUI_INTERNAL_H
