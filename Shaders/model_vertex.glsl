#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
};

out VertexData vertexData;
out vec4 fragColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 color;

void main()
{
	vertexData.worldPosition = vec3(modelMatrix * vec4(position, 1.0f));
	vertexData.texCoords = texCoords;
     fragColor = vec4(color);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}