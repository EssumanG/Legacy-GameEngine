#pragma once 

#include "../../Renderer/Shader.h"
#include <string>
#include <glm/glm.hpp>
namespace Legacy
{
    
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();
        void UploadUniformInt( const std::string& name, int value);

        void UploadUniformFloat( const std::string& name, float value);
        void UploadUniformFloat2( const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3( const std::string& name, const glm::vec3& vlaue);
        void UploadUniformFloat4( const std::string& name, const glm::vec4& value);
        
        void UploadUniformMat3( const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4( const std::string& name, const glm::mat4& matrix);
        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        unsigned int m_RendererID;

    };
    
} // namespace Legacy