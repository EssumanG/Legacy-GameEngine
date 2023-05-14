#pragma once 
#include <string>
#include <glm/glm.hpp>
namespace Legacy
{
    
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void UploadUniformMat4( const std::string& name, const glm::mat4& matrix);
        void Bind() const;
        void Unbind() const;

    private:
        unsigned int m_RendererID;

    };
    
} // namespace Legacy
