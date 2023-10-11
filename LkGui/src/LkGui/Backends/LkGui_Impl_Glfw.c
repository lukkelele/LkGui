#include "LkGui/Backends/LkGui_Impl_Glfw.h"
#include "LkGui/LkGui_Internal.h"
#include "LkGui.h"


LkGui_ImplGlfw_Data* _LkGui_ImplGlfw_Data = NULL;
LkGui_ImplGlfw_Data* _LkGui_ImplGlfw_GetGlfwData() { return _LkGui_ImplGlfw_Data; }

void LkGui_ImplGlfw_Init(bool instant_callbacks)
{
    _LkGui_ImplGlfw_Data = LK_NEW(LkGui_ImplGlfw_Data);
    _LkGui_ImplGlfw_Data->Initialized = true;
    _LkGui_ImplGlfw_Data->InstantCallbacks = instant_callbacks;
}

GLFWwindow* LkGui_ImplGlfw_CreateWindow(const char* title, uint16_t width, uint16_t height, GLFWmonitor* monitor, GLFWwindow* share)
{
    if (!glfwInit())
    {
        printf("[LkGui] Error occured when creating GLFW window\n");
        exit(EXIT_FAILURE);
    }

    LkGui_ImplGlfw_Data* glfwData = _LkGui_ImplGlfw_GetGlfwData();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwData->MainWindowHandle = glfwCreateWindow(width, height, title, monitor, share);
    glfwMakeContextCurrent(glfwData->MainWindowHandle);

    LkGuiContext* ctx = LkGui_GetContext();
    ctx->GlfwWindowHandle = glfwData->MainWindowHandle;
    ctx->ViewportSize = LKVEC2(width, height);
    ctx->WindowSize = LKVEC2(width, height);

    return glfwData->MainWindowHandle;
}

GLFWwindow* LkGui_ImplGlfw_GetMainWindow()
{
    LkGui_ImplGlfw_Data* glfwData = _LkGui_ImplGlfw_GetGlfwData();
    return glfwData->MainWindowHandle;
}
