#ifndef LKGUI_BASE_H
#define LKGUI_BASE_H

#include <assert.h>
#include <stdint.h>

#define LK_NO_ERROR 0
#define LK_ERROR    1

#define LK_UNUSED(_VAR)    ((void)(_VAR))
#define LK_ASSERT(_EXPR)   assert(_EXPR)
#define LK_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR) / sizeof(*(_ARR))))

#endif // LKGUI_BASE_H
