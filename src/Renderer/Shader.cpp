#include "Shader.h"
#include "lg_pch.h"
#include "Core.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Legacy
{
    Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc)
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
    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE,glm::value_ptr(matrix));
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }
    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

} // namespace Legacy
