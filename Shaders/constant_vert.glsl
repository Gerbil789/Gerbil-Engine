#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec4 frag_color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 color;

void main()
{
	frag_color = color;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}

