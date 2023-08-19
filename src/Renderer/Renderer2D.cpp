#include "Renderer2D.h"

#include "Shader.h"
#include "VertexArray.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"


namespace Legacy
{

    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> RectShader;
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::Init()
    {
        s_Data = new Renderer2DStorage();
        s_Data->QuadVertexArray = VertexArray::Create();
        float Rectvertices[]={
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };


    Ref<VertexBuffer> m_RectVertexBuffer;
    m_RectVertexBuffer = VertexBuffer::Create(Rectvertices, sizeof(Rectvertices));
    m_RectVertexBuffer->SetLayout({
        {ShaderDataType::Float3, "a_Position"},
    });

    s_Data->QuadVertexArray->AddVertexBuffer(m_RectVertexBuffer);         
    uint32_t RectIndices[]= {0, 1, 2, 2, 3, 0};
    Ref<IndexBuffer> m_RectIndexBuffer; 
    m_RectIndexBuffer = IndexBuffer::Create(RectIndices, sizeof(RectIndices)/sizeof(uint32_t));
    s_Data->QuadVertexArray->SetIndexBuffer(m_RectIndexBuffer);

    
    s_Data->RectShader = Shader::Create("/home/essuman/projects/C_or_C++_projects/Game Engine/Leagacy/Sandbox/assets/shaders/RectColor.glsl");

    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera)
    {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->RectShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->RectShader)->UploadUniformMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->RectShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
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
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->RectShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->RectShader)->UploadUniformFloat4("u_Color", color);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

} // namespace Legacy

