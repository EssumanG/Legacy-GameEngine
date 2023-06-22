#include "lg_pch.h"
#include "VertexArray.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace Legacy
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: LG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
        }
        LG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Legacy
