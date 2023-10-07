#ifndef LKGUI_LOGGER_H
#define LKGUI_LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define LOG_DEBUG(_MESSAGE, ...) _Log(LOG_LEVEL_DEBUG, _MESSAGE, ##__VA_ARGS__)

typedef enum {
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} LogLevel;

int SetupLogger();
void _Log(LogLevel lvl, const char* msg, ...);


#endif // LKGUI_LOGGER_H
