#include "LkGui/Backends/LkGui_Impl_Glfw.h"
#include "LkGui/LkGui_Internal.h"
#include "LkGui.h"

LkGui_ImplGlfw_Data* _LkGui_ImplGlfw_Data = NULL;

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
    LkGuiContext* ctx = LkGui_GetContext();
    LkGui_ImplGlfw_Data* glfwData = LkGui_ImplGlfw_GetGlfwData();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
    // glfwData->MainWindowHandle = glfwCreateWindow(width, height, title, monitor, share);
    glfwData->MainWindowHandle = window;

    // GLFWwindow* window = glfwData->MainWindowHandle;
    // glfwSetWindowAttrib(window, GLFW_FOCUSED, GL_TRUE);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetMouseButtonCallback(window, LkGui_Mouse_ButtonPressCallback);
    glfwSetCursorPosCallback(window, LkGui_Mouse_CursorPosCallback);
    glfwSetKeyCallback(window, LkGui_Keyboard_KeyCallback);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    ctx->GlfwWindowHandle = glfwData->MainWindowHandle;
    ctx->ViewportSize = LKVEC2(width, height);
    ctx->WindowSize = LKVEC2(width, height);

    glfwMakeContextCurrent(glfwData->MainWindowHandle);

    return glfwData->MainWindowHandle;
}

LkGui_ImplGlfw_Data* LkGui_ImplGlfw_GetGlfwData()
{
    return _LkGui_ImplGlfw_Data;
}

GLFWwindow* LkGui_ImplGlfw_GetMainWindow()
{
    LkGui_ImplGlfw_Data* glfwData = LkGui_ImplGlfw_GetGlfwData();
    return glfwData->MainWindowHandle;
}

void LkGui_Keyboard_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        glfwSetInputMode(_LkGui_ImplGlfw_Data->MainWindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        glfwSetInputMode(_LkGui_ImplGlfw_Data->MainWindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void LkGui_Mouse_ButtonPressCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        LkGuiContext* ctx = LkGui_GetContext();
        printf("Mouse_ButtonPressCallback: Left mousebutton pressed\n");
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        LkGuiContext* ctx = LkGui_GetContext();
        printf("Mouse_ButtonPressCallback: Right mousebutton pressed\n");
        // Reset rendered rectangle (DEBUGGING PURPOSES)
        LkRectangle* rect = ctx->GeometryStorage->Rectangles[0];
        if (rect)
        {
            glm_mat4_identity(rect->Model);
        }
    }
}

void LkGui_Mouse_CursorPosCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    // printf("Mouse_ButtonPressCallback\n");
    LkGui_Mouse_MoveCallback();
}


