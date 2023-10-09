#include "LkGui.h"



//=============================================================================
// [SECTION] LkGui API
//=============================================================================




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
