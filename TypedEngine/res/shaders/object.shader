#shader vertex

#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;

uniform mat4 uMvpMatrix;

out vec2 oTexcoord;

void main() {
	oTexcoord = vec2(texcoord.x, texcoord.y);
	gl_Position = uMvpMatrix * vec4(position, 0.0f, 1.0f);
};

#endshader vertex
#shader fragment

#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 texcoord;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main() {
	FragColor = texture(uTexture, texcoord);
};

#endshader fragment