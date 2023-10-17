#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
	vec4 color;
};

in VertexData vertexData;
out vec4 outColor;

void main()
{
	vec3 lightPosition= vec3(0.0,0.0,0.0); 
	vec3 lightVector = lightPosition - vertexData.worldPosition;
	float diff = max(dot(lightVector, normalize(vertexData.normal)), 0.0); 
	vec4 diffuse = diff * vec4( 1.0, 0.0, 0.0, 1.0); // red diffuse light
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
	outColor = (ambient + diffuse) * vertexData.color;
}