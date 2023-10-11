#ifndef LKGUI_BASE_H
#define LKGUI_BASE_H

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#define LK_UNUSED(_VAR)        ((void)(_VAR))
#define LK_ASSERT(_EXPR)       assert(_EXPR)
#define LK_ARRAYSIZE(_ARR)     ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define LK_NEW(_TYPE)          (_TYPE*)malloc(sizeof(_TYPE))


#endif // LKGUI_BASE_H
