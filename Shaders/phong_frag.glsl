#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

in VertexData vertexData;
out vec4 outColor;

const int MAX_LIGHTS = 4;
uniform Light lights[MAX_LIGHTS];
uniform int numLights; 

uniform Material material;

uniform vec3 cameraPosition;

void main()
{
	vec3 finalColor = vec3(0.0);
	vec3 viewDir = normalize(cameraPosition - vertexData.worldPosition);
    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - vertexData.worldPosition);
        vec3 lightColor = lights[i].color * lights[i].intensity;
		vec3 ambient = lights[i].color * material.ambient;
        vec3 diffuse = lightColor * max(dot(lightDir, normalize(vertexData.normal)), 0.0) * material.diffuse;
		vec3 reflectDir = reflect(-lightDir, vertexData.normal);
        vec3 specular = lightColor * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;

        finalColor += (ambient + diffuse + specular);
    }
	
	outColor = vec4(finalColor, 1.0);
}