#version 330 core

out vec4 outColor;

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
};
in VertexData vertexData;
uniform samplerCube textureUnitID;

void main()
{
	vec3 texColor = texture(textureUnitID, vertexData.texCoords).rgb;
	outColor = vec4(texColor, 1.0);
}