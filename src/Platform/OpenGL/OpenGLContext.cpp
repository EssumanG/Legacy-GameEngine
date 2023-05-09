#include "../../lg_pch.h"
#include "Core.h"

#include "OpenGLContext.h"



namespace Legacy
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        :m_WindowHandle(windowHandle)
    {
        LG_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        LG_CORE_ASSERT(status, "Failed to initialize Glad");
    }

    void OpenGLContext::SwapBuffers()
    {
        glBegin(GL_TRIANGLES);
        glEnd();
        glfwSwapBuffers(m_WindowHandle);
    }

} // namespace Legacy
