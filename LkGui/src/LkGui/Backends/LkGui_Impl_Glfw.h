#ifndef LKGUI_BACKEND_IMPL_GLFW
#define LKGUI_BACKEND_IMPL_GLFW
#include <ctype.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include "LkGui_Impl_Base.h"

// Forward declarations
typedef struct GLFWwindow  GLFWwindow;
typedef struct GLFWmonitor GLFWmonitor;
typedef struct LkGui_ImplGlfw_Data LkGui_ImplGlfw_Data;

struct LkGui_ImplGlfw_Data
{
    GLFWwindow*   MainWindowHandle;
    bool          Initialized;
    bool          InstantCallbacks;
};


void LkGui_ImplGlfw_Init(bool instant_callbacks);
GLFWwindow* LkGui_ImplGlfw_CreateWindow(const char* title, uint16_t width, uint16_t height, GLFWmonitor* monitor, GLFWwindow* share);
GLFWwindow* LkGui_ImplGlfw_GetMainWindow();

LkGui_ImplGlfw_Data* _LkGui_ImplGlfw_GetGlfwData();


#endif // LKGUI_BACKEND_IMPL_GLFW
