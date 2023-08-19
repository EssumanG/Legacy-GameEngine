#include "lg_pch.h"

#include "Renderer.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Legacy
{
    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
   
    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }
    void Renderer::OnWindowResized(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewPort(0, 0, width, height);
    }
    void Renderer::BeginScene(OrthographicCamera &camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray> &vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
        vertexArray->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }

} // namespace Legacy
