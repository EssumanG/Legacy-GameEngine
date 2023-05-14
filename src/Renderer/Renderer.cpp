#include "lg_pch.h"

#include "Renderer.h"

namespace Legacy
{
    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> &vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
        vertexArray->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }

} // namespace Legacy