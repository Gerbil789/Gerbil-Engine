#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
	vec4 color;
};

out VertexData vertexData;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
uniform vec4 color;

void main()
{
	vertexData.worldPosition = vec3(modelMatrix * vec4(position, 1.0f));
	vertexData.normal = normal * normalMatrix;
	vertexData.texCoords = texCoords;
    vertexData.color = vec4(color);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}

