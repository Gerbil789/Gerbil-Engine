#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
	vec4 color;
};

in VertexData vertexData;

out vec4 outColor;
uniform vec3 lightPosition;

void main()
{
	vec3 lightVector = normalize(lightPosition - vertexData.worldPosition);
	float diff = max(dot(lightVector, normalize(vertexData.normal)), 0.0); 
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
	vec4 lightColor = vec4( 1.0, 1.0, 1.0, 1.0); //white
	outColor = (ambient + (diff * lightColor)) * vertexData.color;
}