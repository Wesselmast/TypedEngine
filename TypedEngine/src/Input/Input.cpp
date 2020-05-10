#include "Input.h"

// TODO @CleanUp: RendererAPI that takes in different API's here

#include "OpenGL/OpenGLInputManager.h"

InputManager* Input::inputManager = new OpenGLInputManager();
