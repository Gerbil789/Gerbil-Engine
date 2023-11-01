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

struct DirectionalLight {
    vec3 color;
    float intensity;
    vec3 direction;
};

in VertexData vertexData;
out vec4 outColor;

const int MAX_POINT_LIGHT = 10;
uniform Light pointLights[MAX_POINT_LIGHT];
uniform int pointLightCount; 

const int MAX_DIR_LIGHT = 5;
uniform DirectionalLight directionalLights[MAX_DIR_LIGHT];
uniform int directionalLightCount; 

uniform Material material;
uniform vec3 cameraPosition;
uniform vec3 color;

void main()
{
	vec3 finalColor = vec3(0.0);
	vec3 viewDir = normalize(cameraPosition - vertexData.worldPosition);

    // Point lights
    for (int i = 0; i < pointLightCount; i++) {
        vec3 lightDir = normalize(pointLights[i].position - vertexData.worldPosition);

		float distance = length(pointLights[i].position - vertexData.worldPosition);
		float constant = 0.1;
        float linear = 1.0;
        float quadratic = 0.032;
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        vec3 lightColor = pointLights[i].color * pointLights[i].intensity;
        vec3 diffuse = lightColor * max(dot(lightDir, normalize(vertexData.normal)), 0.0);
        
		vec3 reflectDir = reflect(-lightDir, normalize(vertexData.normal));
        vec3 specular = lightColor * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;

        finalColor += (material.ambient + attenuation * (diffuse + specular));
    }

    // Direcional lights
    for (int i = 0; i < directionalLightCount; i++) {

        vec3 lightColor = directionalLights[i].color * directionalLights[i].intensity;
        vec3 diffuse = lightColor * max(dot( -directionalLights[i].direction, normalize(vertexData.normal)), 0.0);
        
		vec3 reflectDir = reflect(directionalLights[i].direction, normalize(vertexData.normal));
        vec3 specular = lightColor * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;

        finalColor += (material.ambient + (diffuse + specular));
    }

	finalColor = finalColor * color;
	outColor = vec4(finalColor, 1.0);
}