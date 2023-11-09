#version 330 core

out vec4 outColor;
uniform vec3 color;

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
};
in VertexData vertexData;
uniform sampler2D textureUnitID;

void main()
{
	outColor = vec4(color, 1.0) * texture(textureUnitID, vertexData.texCoords);
}