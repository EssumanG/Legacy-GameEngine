#include "OpenGLShader.h"
#include "Core.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Legacy
{
    OpenGLShader::OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar* source = (const GLchar*)vertexSrc.c_str();
        glShaderSource(VertexShader, 1, &source, 0);

        glCompileShader(VertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(VertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(VertexShader);

            std::cout <<  &infoLog[0] << std::endl;
            LG_CORE_ASSERT(false, " vertex shader compilation failure!");
            return;
        }



        GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = (const GLchar*)fragmentSrc.c_str();
        glShaderSource(FragmentShader, 1, &source, 0);

        glCompileShader(FragmentShader);

        glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(FragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(FragmentShader);

            glDeleteShader(VertexShader);

            std::cout <<  &infoLog[0] << std::endl;
            LG_CORE_ASSERT(false, " fragment shader compilation failure!");
            return;
        }


        m_RendererID = glCreateProgram();

        glAttachShader(m_RendererID, VertexShader);
        glAttachShader(m_RendererID, FragmentShader);

        glLinkProgram(m_RendererID);

        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_RendererID);

            glDeleteShader(FragmentShader);

            glDeleteShader(VertexShader);

            std::cout <<  &infoLog[0] << std::endl;
            LG_CORE_ASSERT(false, " shader link failure!");
            return;


        }

        glDetachShader(m_RendererID, VertexShader);
        glDetachShader(m_RendererID, FragmentShader);
    }
    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, int value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string &name, float value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE,glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE,glm::value_ptr(matrix));
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }
    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

} // namespace Legacy
