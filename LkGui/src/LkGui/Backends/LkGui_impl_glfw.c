#include "LkGui/Backends/LkGui_impl_glfw.h"
#include "LkGui/Core/Context.h"

LkGui_ImplGlfw_Data* _LkGui_ImplGlfw_Data = NULL;

LkGui_ImplGlfw_Data* _LkGui_ImplGlfw_GetGlfwData()
{
    return _LkGui_ImplGlfw_Data;
}


void LkGui_ImplGlfw_Init(bool instant_callbacks)
{
    _LkGui_ImplGlfw_Data = (LkGui_ImplGlfw_Data*)malloc(sizeof(LkGui_ImplGlfw_Data));
    LkContext* ctx = LkGui_GetContext();
    ctx->MainWindow = NULL;
    _LkGui_ImplGlfw_Data->Initialized = true;
}

GLFWwindow* LkGui_ImplGlfw_CreateWindow(const char* title, uint16_t width, uint16_t height, GLFWmonitor* monitor, GLFWwindow* share)
{
    // LkGui_ImplGlfw_Data glfwData = *_LkGui_ImplGlfw_GetGlfwData();
    LkGui_ImplGlfw_Data* glfwData = _LkGui_ImplGlfw_GetGlfwData();
    // ctx->MainWindow = glfwCreateWindow(width, height, title, monitor, share);
    glfwData->MainWindowHandle = glfwCreateWindow(width, height, title, monitor, share);
    glfwMakeContextCurrent(glfwData->MainWindowHandle);

    return glfwData->MainWindowHandle;
}


GLFWwindow* LkGui_ImplGlfw_GetMainWindow()
{
    LkGui_ImplGlfw_Data* glfwData = _LkGui_ImplGlfw_GetGlfwData();
    return glfwData->MainWindowHandle;
}
