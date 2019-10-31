// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: RenderCommand.cpp
// Date: 31/10/2019

#include "mdpch.h"
#include "RenderCommand.h"
#include "platform/opengl/OpenGLRendererAPI.h"

namespace midori {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
