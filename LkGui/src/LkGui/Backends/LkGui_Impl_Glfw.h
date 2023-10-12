#ifndef LKGUI_BACKEND_IMPL_GLFW
#define LKGUI_BACKEND_IMPL_GLFW
#include <ctype.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>

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


void                  LkGui_ImplGlfw_Init(bool instant_callbacks);
GLFWwindow*           LkGui_ImplGlfw_CreateWindow(const char* title, uint16_t width, uint16_t height, GLFWmonitor* monitor, GLFWwindow* share);
GLFWwindow*           LkGui_ImplGlfw_GetMainWindow();
LkGui_ImplGlfw_Data*  LkGui_ImplGlfw_GetGlfwData();
void                  LkGui_Keyboard_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void                  LkGui_Mouse_ButtonPressCallback(GLFWwindow* window, int button, int action, int mods);
void                  LkGui_Mouse_CursorPosCallback(GLFWwindow* window, double x_pos, double y_pos);



#endif // LKGUI_BACKEND_IMPL_GLFW
