#include "LkGui/Core/Logger.h"


int SetupLogger()
{
    return 0;
}

void _Log(LogLevel lvl, const char* msg, ...)
{
    char timestampBuf[40];
    char buf[120];
    // char* timestampFormat = "%Y-%m-%d %H:%M:%S";
    char* timestampFormat = "%H:%M:%S";
    time_t t;
    struct tm* ltime;

    time(&t);
    ltime = localtime(&t);
    // strftime(timestampBuf, sizeof(timestampBuf), "%Y-%m-%d %H:%M:%S", ltime);
    strftime(timestampBuf, sizeof(timestampBuf), timestampFormat, ltime);
    printf("%s ", timestampBuf);

    switch (lvl)
    {
        case LOG_LEVEL_TRACE:  printf("[TRACE] ");  break;
        case LOG_LEVEL_DEBUG:  printf("[DEBUG] ");  break;
        case LOG_LEVEL_INFO:   printf("[INFO] ");  break;
        case LOG_LEVEL_WARN:   printf("[WARN] ");  break;
        case LOG_LEVEL_ERROR:  printf("[ERROR] "); break;
    }
    printf("%s", buf);

    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    printf("\n");
}
