#include "lg_pch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Legacy 
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}