#pragma once 

#include "Renderer/RendererAPI.h"
namespace Legacy
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
    
} // namespace Legacy
