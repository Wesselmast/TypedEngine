#include "RenderCommand.h"

#include "OpenGL/OpenGLRenderer.h"

	// TODO @CleanUp: RendererAPI that takes in different API's here

Renderer* RenderCommand::renderer = new OpenGLRenderer();