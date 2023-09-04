#include "Renderer2D.h"

#include "Shader.h"
#include "VertexArray.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Legacy
{

    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> RectShader;
        Ref<Shader> TextureShader;
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::Init()
    {
        s_Data = new Renderer2DStorage();
        s_Data->QuadVertexArray = VertexArray::Create();
        float Rectvertices[]={
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };


    Ref<VertexBuffer> m_RectVertexBuffer;
    m_RectVertexBuffer = VertexBuffer::Create(Rectvertices, sizeof(Rectvertices));
    m_RectVertexBuffer->SetLayout({
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "a_TexCoord"}
    });

    s_Data->QuadVertexArray->AddVertexBuffer(m_RectVertexBuffer);         
    uint32_t RectIndices[]= {0, 1, 2, 2, 3, 0};
    Ref<IndexBuffer> m_RectIndexBuffer; 
    m_RectIndexBuffer = IndexBuffer::Create(RectIndices, sizeof(RectIndices)/sizeof(uint32_t));
    s_Data->QuadVertexArray->SetIndexBuffer(m_RectIndexBuffer);

    
    s_Data->RectShader = Shader::Create("/home/essuman/projects/C_or_C++_projects/Game Engine/Leagacy/Sandbox/assets/shaders/RectColor.glsl");
    s_Data->TextureShader = Shader::Create("/home/essuman/projects/C_or_C++_projects/Game Engine/Leagacy/Sandbox/assets/shaders/Texture.glsl");
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetInt("u_Texture", 0);

    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera)
    {
        s_Data->RectShader->Bind();
        s_Data->RectShader->SetMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
        
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawQuad({position.x,position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        s_Data->RectShader->Bind();
        s_Data->RectShader->SetFloat4("u_Color", color);
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0), {size.x, size.y, 1.0f});
        s_Data->RectShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture)
    {
        DrawQuad({position.x,position.y, 0.0f}, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture)
    {
        s_Data->TextureShader->Bind();

        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0), {size.x, size.y, 1.0f});
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        texture->Bind();

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

} // namespace Legacy

