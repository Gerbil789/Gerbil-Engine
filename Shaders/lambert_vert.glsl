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
out mat4 model;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vertexData.worldPosition = vec3(modelMatrix * vec4(position, 1.0f));
	vertexData.normal = mat3(transpose(inverse(modelMatrix))) * normal;
	vertexData.texCoords = texCoords;

	model = modelMatrix;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}

