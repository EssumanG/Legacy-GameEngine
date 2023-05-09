#pragma once 

#include "../../Renderer/GraphicsContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h" 


namespace Legacy
{
    class OpenGLContext: public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* WindowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow *m_WindowHandle;
    };
    
} // namespace Legacy
