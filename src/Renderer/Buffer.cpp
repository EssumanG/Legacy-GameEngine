
#include "Buffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Legacy
{
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: LG_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        }
        LG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: LG_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
        }
        LG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Legacy
