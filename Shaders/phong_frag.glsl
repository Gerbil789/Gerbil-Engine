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
uniform vec3 cameraPosition;
uniform float specularStrength;

void main()
{
	vec3 lightVector = normalize(lightPosition - vertexData.worldPosition);
	float diff = max(dot(lightVector, normalize(vertexData.normal)), 0.0); 

	vec3 viewDir = normalize(cameraPosition - vertexData.worldPosition);
	vec3 reflectDir = reflect (-lightVector, vertexData.normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularStrength);
	vec4 specular = vec4(1.0, 1.0, 1.0, 1.0) * spec;

    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
	
	outColor = (ambient + diff + specular) * vertexData.color;
}