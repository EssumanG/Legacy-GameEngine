#include "lg_pch.h"
#include "Shader.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Legacy
{
    Shader *Shader::Create(const std::string &filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: LG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
        }
        LG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;

    }

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: LG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        LG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Legacy
