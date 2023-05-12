#include "lg_pch.h"
#include "VertexArray.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace Legacy
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: LG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
            case RendererAPI::OpenGL: return new OpenGLVertexArray();
        }
        LG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Legacy
