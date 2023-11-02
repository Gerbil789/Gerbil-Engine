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

const int MAX_LIGHTS = 10;
uniform Light lights[MAX_LIGHTS];
uniform int numLights; 
uniform Material material;
uniform vec3 cameraPosition;
uniform vec3 color;

void main()
{
	vec3 finalColor = vec3(0.0);
	vec3 viewDir = normalize(cameraPosition - vertexData.worldPosition);
    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - vertexData.worldPosition);

		float distance = length(lights[i].position - vertexData.worldPosition);
		float constant = 0.1;
        float linear = 1.0;
        float quadratic = 0.032;
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        vec3 lightColor = lights[i].color * lights[i].intensity;
        vec3 diffuse = lightColor * max(dot(lightDir, normalize(vertexData.normal)), 0.0);
        
		vec3 halfwayDir = normalize(lightDir + viewDir);

        vec3 specular = lightColor * pow(max(dot(normalize(vertexData.normal), halfwayDir), 0.0), material.shininess) * material.specular;

        finalColor += (material.ambient + attenuation * (diffuse + specular));
    }
	finalColor = finalColor * color;
	outColor = vec4(finalColor, 1.0);
}