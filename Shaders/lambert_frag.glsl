#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
};

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in VertexData vertexData;

out vec4 outColor;

const int MAX_LIGHTS = 10;
uniform Light lights[MAX_LIGHTS];
uniform int numLights; 
uniform Material material;
uniform vec3 color;

void main()
{
	vec3 finalColor = vec3(0.0);
    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - vertexData.worldPosition);
        vec3 lightColor = lights[i].color * lights[i].intensity;

        vec3 diffuse = lightColor * max(dot(lightDir, normalize(vertexData.normal)), 0.0);
		
        finalColor += diffuse;
    }

	outColor = (vec4(material.ambient, 1.0) + vec4(finalColor, 1.0)) * vec4(color, 1.0);
}