#pragma once

#include "../../Renderer/Shader.h"
#include <string>
#include <glm/glm.hpp>

// TODO: REMOVE!!
typedef unsigned int GLenum;
namespace Legacy
{

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &filepath);
        OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
        ~OpenGLShader();

        virtual void SetInt(const std::string& name, int value) override;
        virtual void SetFloat3(const std::string& name, const glm::vec3 &value) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4 &value) override;
        virtual void SetMat4(const std::string& name, const glm::mat4 &value) override;

        void UploadUniformInt(const std::string &name, int value);

        void UploadUniformFloat(const std::string &name, float value);
        void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);
        void UploadUniformFloat3(const std::string &name, const glm::vec3 &vlaue);
        void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

        void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
        void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const std::string &GetName() const override { return m_Name; }

    private:
        std::string ReadFile(const std::string &filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
        void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);

    private:
        unsigned int m_RendererID;
        std::string m_Name;
    };

} // namespace Legacy
