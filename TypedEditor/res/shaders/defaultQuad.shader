#shader vertex

#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 uMvpMatrix;
uniform vec2 uSize;

void main() {
  gl_Position = uMvpMatrix * vec4(position.x * uSize.x, position.y * uSize.y, 0.0f, 1.0f);
};

#endshader vertex
#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

const float offset = 1.0 / 128.0; 
uniform vec4 uColor;
uniform int uClicked;

void main() {
  if(uClicked == 1) {
    color = vec4(0.0, 0.8, 0.0, 1.0);
  }
  else {
    color = uColor;
  }
};

#endshader fragment
