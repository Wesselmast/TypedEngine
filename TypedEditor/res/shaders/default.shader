#shader vertex

#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;

uniform sampler2D uTexture;
uniform mat4 uMvpMatrix;

out vec2 vTexcoord;

void main() {
  gl_Position = uMvpMatrix * vec4(position * textureSize(uTexture, 0), 0.0f, 1.0f);
  vTexcoord = texcoord;
};

#endshader vertex
#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTexcoord;

const float offset = 1.0 / 48.0; 
uniform sampler2D uTexture;
uniform int uClicked;

void main() {
  vec4 col = texture(uTexture, vTexcoord);
  if(uClicked == 1) {
    if(vTexcoord.x < offset || vTexcoord.x > 1.0 - offset ||
       vTexcoord.y < offset || vTexcoord.y > 1.0 - offset) {
      color = vec4(0.0, 0.8, 0.0, 1.0);
    }
    else {
      color = col;
    }
  }
  else {
    color = col;
  }
};

#endshader fragment
