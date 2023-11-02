#include "lg_pch.h"
#include "UnixWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"


namespace Legacy
{
    
    static bool s_GLFWInitialized = false;
    static void GLFWErrorCallback(int error, const char* description)
    {
        LG_CORE_ERROR("GLFW Error {0}: ", error, description);
    }

    Window* Window::Create(const WindowProps& props)
    {
        return new UnixWindow(props);
    }

    UnixWindow::UnixWindow(const WindowProps& props)
    {
        LG_PROFILE_FUNCTION();
        Init(props);
    }

    UnixWindow::~UnixWindow()
    {
        LG_PROFILE_FUNCTION();

        ShutDown();
    }

    void UnixWindow::OnUpdate()
    {
        LG_PROFILE_FUNCTION();

        glfwPollEvents();
        m_Context->SwapBuffers();

    }

    void UnixWindow::SetVSync(bool enabled)
    {
        LG_PROFILE_FUNCTION();

        if(enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled; 
    }

    bool UnixWindow::isVSync() const
    {
        return m_Data.VSync;
    }

    void UnixWindow::Init(const WindowProps &props)
    {
        LG_PROFILE_FUNCTION();

        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        LG_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);
        // LG_CORE_INFO("{}",glfwGetVersionString());/
        
        

        if(!s_GLFWInitialized)
        {
            LG_PROFILE_SCOPE("glfwInit");
            int success = glfwInit();
            LG_CORE_ASSERT(success, "Could not Initialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        {
            LG_PROFILE_SCOPE("glfwCreateWindow");
            m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
            m_Context = new OpenGLContext(m_Window);
            m_Context->Init();
        }
        
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        //Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizedEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }  
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }

        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
        });
        

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });
    }

    void UnixWindow::ShutDown()
    {
        LG_PROFILE_FUNCTION();

        glfwDestroyWindow(m_Window);
    }


} // namespace Legacy
