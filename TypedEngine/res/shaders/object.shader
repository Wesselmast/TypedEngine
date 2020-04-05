#shader vertex

#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 uMvpMatrix;

void main() {
	gl_Position = uMvpMatrix * vec4(position, 0.0f, 1.0f);
};

#endshader vertex
#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 uColor;

void main() {
	color = uColor;
};

#endshader fragment