#include "../../lg_pch.h"
#include "Core/Core.h"

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

        // LG_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
        // LG_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
        // LG_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glBegin(GL_TRIANGLES);
        glEnd();
        glfwSwapBuffers(m_WindowHandle);
    }

} // namespace Legacy
