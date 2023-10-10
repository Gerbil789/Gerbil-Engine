#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
};

in VertexData vertexData;
in vec4 fragColor;
out vec4 outColor;

void main()
{
	outColor = fragColor;
}