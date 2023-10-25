#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
	vec4 color;
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

uniform vec3 lightPosition;

void main()
{
	vec3 finalColor = vec3(0.0);
    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - vertexData.worldPosition);
        vec3 lightColor = lights[i].color * lights[i].intensity;

        vec3 diffuse = lightColor * max(dot(lightDir, normalize(vertexData.normal)), 0.0);
		
        finalColor += diffuse;
    }

    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
	outColor = (ambient + vec4(finalColor, 1.0)) * vertexData.color;
}