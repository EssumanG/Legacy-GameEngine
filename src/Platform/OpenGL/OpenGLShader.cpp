#include "OpenGLShader.h"
#include "Core/Core.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Legacy
{

    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        LG_CORE_ASSERT(false, "Unknown Shader type ");
        return 0;
    }
    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        LG_PROFILE_FUNCTION();
        
        std::string source = ReadFile(filepath);
        auto shaderSources = PreProcess(source);
        Compile(shaderSources);


        //Extract name from filepath  
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;

        m_Name = filepath.substr(lastSlash, count);
        
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc)
        :m_Name(name)
    {
        LG_PROFILE_FUNCTION();
        
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);

    }
    OpenGLShader::~OpenGLShader()
    {
        LG_PROFILE_FUNCTION();
        
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::SetInt(const std::string &name, int value)
    {
        LG_PROFILE_FUNCTION();
        
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value)
    {
        LG_PROFILE_FUNCTION();
        
        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4 &value)
    {
        LG_PROFILE_FUNCTION();
        
        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4 &value)
    {
        LG_PROFILE_FUNCTION();
        
        UploadUniformMat4(name, value);
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        LG_PROFILE_FUNCTION();
        
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else 
        {
            LG_CORE_ERROR("Could not open file '{0}'", filepath);
        }
        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        LG_PROFILE_FUNCTION();
        
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);

        while ( pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            LG_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            LG_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specificied");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        LG_PROFILE_FUNCTION();
        
        GLuint program = glCreateProgram();
        LG_CORE_ASSERT(shaderSources.size() <= 2, "Only support 2 shaders for now");
        std::array<GLenum, 2> glShaderIds;
        int glShaderIDInndex = 0;
        for (auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;
            
            GLuint shader = glCreateShader(type);

            const GLchar* sourceCstr = (const GLchar*)source.c_str();
            glShaderSource(shader, 1, &sourceCstr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                std::cout <<  &infoLog[0] << std::endl;
                LG_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }
            glAttachShader(program, shader);
            glShaderIds[glShaderIDInndex++] = shader;
        }    

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            for(auto id : glShaderIds)
                glDeleteShader(id);

            std::cout <<  &infoLog[0] << std::endl;
            LG_CORE_ASSERT(false, " shader link failure!");
            return;


        }

        for(auto id : glShaderIds)
            glDetachShader(program, id);

        m_RendererID = program;
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
        LG_PROFILE_FUNCTION();
        
        glUseProgram(m_RendererID);
    }
    void OpenGLShader::Unbind() const
    {
        LG_PROFILE_FUNCTION();
        
        glUseProgram(0);
    }

} // namespace Legacy
