#include "LkGui/Backends/LkGui_impl_opengl4.h"
#include <GLFW/glfw3.h>
#include <stdio.h>


unsigned int LkGui_ImplOpenGL4_Init()
{
    GLenum err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (err == 0)
    {
        printf("[ERROR] Error occured when initializing glad");
        return LK_ERROR;
    }
    else
    {
        printf("[LkGui] OpenGL Version: %s\n", glGetString(GL_VERSION));
    }
    return LK_NO_ERROR;
}
